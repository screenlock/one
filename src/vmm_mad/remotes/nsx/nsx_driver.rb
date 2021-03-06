# ---------------------------------------------------------------------------- #
# Copyright 2002-2019, OpenNebula Project, OpenNebula Systems                  #
#                                                                              #
# Licensed under the Apache License, Version 2.0 (the "License"); you may      #
# not use this file except in compliance with the License. You may obtain      #
# a copy of the License at                                                     #
#                                                                              #
# http://www.apache.org/licenses/LICENSE-2.0                                   #
#                                                                              #
# Unless required by applicable law or agreed to in writing, software          #
# distributed under the License is distributed on an "AS IS" BASIS,            #
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.     #
# See the License for the specific language governing permissions and          #
# limitations under the License.                                               #
# ---------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------- #
# Set up the environment for the driver                                        #
# ---------------------------------------------------------------------------- #

ONE_LOCATION = ENV['ONE_LOCATION'] unless defined?(ONE_LOCATION)

if !ONE_LOCATION
    BIN_LOCATION = '/usr/bin'     unless defined?(BIN_LOCATION)
    LIB_LOCATION = '/usr/lib/one' unless defined?(LIB_LOCATION)
    ETC_LOCATION = '/etc/one/'    unless defined?(ETC_LOCATION)
    VAR_LOCATION = '/var/lib/one' unless defined?(VAR_LOCATION)
else
    BIN_LOCATION = ONE_LOCATION + '/bin' unless defined?(BIN_LOCATION)
    LIB_LOCATION = ONE_LOCATION + '/lib'  unless defined?(LIB_LOCATION)
    ETC_LOCATION = ONE_LOCATION + '/etc/' unless defined?(ETC_LOCATION)
    VAR_LOCATION = ONE_LOCATION + '/var/' unless defined?(VAR_LOCATION)
end

ENV['LANG'] = 'C'

$LOAD_PATH << LIB_LOCATION + '/ruby'
$LOAD_PATH << LIB_LOCATION + '/ruby/nsx_driver'

# ---------------------------------------------------------------------------- #
# NSX Library                                                                  #
# ---------------------------------------------------------------------------- #
require 'logical_switch'
require 'nsx_client'
require 'opaque_network'
require 'virtual_wire'

# NSX Driver module
module NSXDriver
end
