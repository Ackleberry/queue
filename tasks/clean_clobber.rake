#file    clean_clobber.rake
#author  Brooks Anderson
#brief   Tasks that invoke all other clean and clobber tasks
#deps    none
#config  none

desc "Invokes all other 'clean' tasks"
task "clean" do |task|
  all_tasks = Rake.application.tasks
  clean_tasks = all_tasks.filter_map { |key, val| if key.to_s.include?(':clean') then key end }
  clean_tasks.each { |t| Rake::Task[t].invoke }
end

desc "Invokes all other 'clobber' tasks"
task "clobber": "clean" do |task|
  all_tasks = Rake.application.tasks
  clobber_tasks = all_tasks.filter_map { |key, val| if key.to_s.include?(':clobber') then key end }
  clobber_tasks.each { |t| Rake::Task[t].invoke }
end