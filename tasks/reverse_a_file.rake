#file    test.rake
#author  Brooks Anderson
#brief   Contains tasks for unit tests
#deps    gcc installation
#config  Refer to `examples/rake_config.yml` for required yaml configuration.

# Create YAML config alias
cfg_name = :reverse_a_file
cfg = $cfg[cfg_name]
src = Rake::FileList[cfg[:src_files]]

# Map contains hashes relating all build files back to the source files.
# Example: Path/to/SomeFancyFile.o => Some/Other/Path/to/SomeFancyFile.c
map = {
  obj_hash: src.pathmap("#{cfg[:output_path]}/obj/%n.o").zip(src).to_h,
  mf_hash: src.pathmap("#{cfg[:output_path]}/dep/%n.mf").zip(src).to_h
}

# Default task
desc "Run #{cfg_name}"
task "#{cfg_name}": ["#{cfg_name}:run"]

namespace "#{cfg_name}" do

  desc "Remove all intermediate test files"
  task "clean" do |task|
    rm_rf "#{cfg[:output_path]}/obj"
    rm_rf "#{cfg[:output_path]}/dep"
    rm_rf "#{cfg[:output_path]}/#{cfg[:name]}.dis"
  end

  task "clobber" do |task|
    rm_rf "#{cfg[:output_path]}"
  end

  desc "Build unit tests"
  task "build": "#{cfg[:output_path]}/#{cfg[:name]}.exe"

  desc "Generate disassembly for test exe"
  task "dis": "#{cfg[:output_path]}/#{cfg[:name]}.exe" do |task|
    sh "objdump -S --disassemble #{task.source} > #{cfg[:output_path]}/#{cfg[:name]}.dis"
  end

  task "run": "build" do |task|
    sh "./#{cfg[:output_path]}/#{cfg[:name]}.exe"
  end

end

file "#{cfg[:output_path]}/#{cfg[:name]}.exe": map[:obj_hash].keys do |task|
  obj_files = task.prerequisites.join(' ')
  compiler_args = cfg[:comp_args]&.join(' ')

  sh "#{cfg[:comp_path]}/gcc #{obj_files} #{compiler_args} -o #{task.name}"
  sh "size #{task.source}"
end

# This rule synthesizes tasks for all unique object files. GCC preprocessor is
# used to output dependency files during compilation. Useful dependency options:
# https://gcc.gnu.org/onlinedocs/gcc-7.2.0/gcc/Preprocessor-Options.html
rule %r{#{cfg[:output_path]}/obj/\w+\.o} do |task|
  src_file = map[:obj_hash][task.name]
  mf_file = task.name.pathmap('%{/obj/,/dep/}X.mf')

  compiler_args = cfg[:comp_args]&.join(' ')
  mf_args = "-MMD -MP -MT #{mf_file} -MT #{task.name} -MF #{mf_file}"
  defs = cfg[:defines][:items].map{ |item| cfg[:defines][:prefix]+item }&.join(' ')
  incs = cfg[:includes][:items]&.map{ |item| cfg[:includes][:prefix]+item }&.join(' ')

  mkdir_p [File.dirname(task.name), File.dirname(mf_file)], verbose: false
  sh "#{cfg[:comp_path]}/gcc #{compiler_args} #{mf_args} #{defs} #{incs} -o #{task.name} -c #{src_file}"
  puts ''
end

# Import the '.mf' dependency file if it exists. In makefiles this usually a
# '.d' file. The file contains '.mf' and '.o' file tasks that are dependent on
# various .h and .c files. This allows rake to perform incremental builds. It is
# updated every time the object file rule is called.
map[:mf_hash].keys.each do |dep|
  import dep if File.exist?(dep)
end