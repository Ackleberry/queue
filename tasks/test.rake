#file    test.rake
#author  Brooks Anderson
#brief   Contains tasks for unit tests
#deps    gcc installation
#config  Refer to `examples/rake_config.yml` for required yaml configuration.

# Create YAML config alias
TEST = $cfg[:test]
TEST_SRC = Rake::FileList[TEST[:src_files]]

# Map contains hashes relating all build files back to the source files.
# Example: Path/to/SomeFancyFile.o => Some/Other/Path/to/SomeFancyFile.c
UT_MAP = {
  obj_hash: TEST_SRC.pathmap("#{TEST[:output_path]}/obj/%n.o").zip(TEST_SRC).to_h,
  mf_hash: TEST_SRC.pathmap("#{TEST[:output_path]}/dep/%n.mf").zip(TEST_SRC).to_h
}

# Default task
desc "Run unit tests and print results"
task "test": ["test:run"]

namespace "test" do

  desc "Remove all intermediate test files"
  task "clean" do |task|
    rm_rf "#{TEST[:output_path]}/obj"
    rm_rf "#{TEST[:output_path]}/dep"
    rm_rf "#{TEST[:output_path]}/#{TEST[:name]}.dis"
  end

  task "clobber" do |task|
    rm_rf "#{TEST[:output_path]}"
  end

  desc "Build unit tests"
  task "build": "#{TEST[:output_path]}/#{TEST[:name]}.exe"

  desc "Generate disassembly for test exe"
  task "dis": "#{TEST[:output_path]}/#{TEST[:name]}.exe" do |task|
    sh "objdump -S --disassemble #{task.source} > #{TEST[:output_path]}/#{TEST[:name]}.dis"
  end

  task "run": "build" do |task|
    sh "./#{TEST[:output_path]}/#{TEST[:name]}.exe -v | test/greenest"
  end

end

file "#{TEST[:output_path]}/#{TEST[:name]}.exe": UT_MAP[:obj_hash].keys do |task|
  obj_files = task.prerequisites.join(' ')
  compiler_args = TEST[:comp_args]&.join(' ')

  sh "#{TEST[:comp_path]}/gcc #{obj_files} #{compiler_args} -o #{task.name}"
  sh "size #{task.source}"
end

# This rule synthesizes tasks for all unique object files. GCC preprocessor is
# used to output dependency files during compilation. Useful dependency options:
# https://gcc.gnu.org/onlinedocs/gcc-7.2.0/gcc/Preprocessor-Options.html
rule %r{#{TEST[:output_path]}/obj/\w+\.o} do |task|
  src_file = UT_MAP[:obj_hash][task.name]
  mf_file = task.name.pathmap('%{/obj/,/dep/}X.mf')

  compiler_args = TEST[:comp_args]&.join(' ')
  mf_args = "-MMD -MP -MT #{mf_file} -MT #{task.name} -MF #{mf_file}"
  defs = TEST[:defines][:items].map{ |item| TEST[:defines][:prefix]+item }&.join(' ')
  incs = TEST[:includes][:items]&.map{ |item| TEST[:includes][:prefix]+item }&.join(' ')

  mkdir_p [File.dirname(task.name), File.dirname(mf_file)], verbose: false
  sh "#{TEST[:comp_path]}/gcc #{compiler_args} #{mf_args} #{defs} #{incs} -o #{task.name} -c #{src_file}"
  puts ''
end

# Import the '.mf' dependency file if it exists. In makefiles this usually a
# '.d' file. The file contains '.mf' and '.o' file tasks that are dependent on
# various .h and .c files. This allows rake to perform incremental builds. It is
# updated every time the object file rule is called.
UT_MAP[:mf_hash].keys.each do |dep|
  import dep if File.exist?(dep)
end