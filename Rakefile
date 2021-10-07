require 'rake/loaders/makefile'
require 'yaml'

################################################################################
#                       Load the desired rakefile tasks                        #
# Single file  :    import 'location/of/file.rake'         (recommended)       #
# Entire folder:    Rake.add_rakelib 'some/folder/path'    (risky)             #
################################################################################
Rake.add_rakelib 'tasks'

################################################################################
#                      Load Rake Task Configuration File                       #
# Project supported rake task configurations need to be placed in this file.   #
# Example: $cfg = YAML.load(File.read('some/location/of/rake_config.yaml'))    #
################################################################################
$cfg = YAML.load_file('rake_config.yml')

################################################################################
#                         Project Specific Rake Tasks                          #
################################################################################

task default: 'test:run'