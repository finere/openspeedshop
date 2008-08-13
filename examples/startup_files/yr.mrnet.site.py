##===========================================================================##
#  Copyright (C) 2008 Los Alamos National Security, LLC. All Rights Reserved. #
#               Author: Samuel K. Gutierrez - samuel[at]lanl.gov              #
##===========================================================================##

#=============================================================================#
# This program is free software; you can redistribute it and/or modify it     #
# under the terms of the GNU General Public License as published by the Free  #
# Software Foundation; either version 2 of the License, or (at your option)   #
# any later version.                                                          #
#                                                                             #
# This program is distributed in the hope that it will be useful, but WITHOUT #
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       #
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for   #
# more details.                                                               #
#                                                                             #
# You should have received a copy of the GNU General Public License along     #
# with this program; if not, write to the Free Software Foundation, Inc., 59  #
# Temple Place, Suite 330, Boston, MA  02111-1307 USA                         #
#=============================================================================#

#LANL's Yellowrail MRNet site.py

import commands
from re import compile
from sets import Set
from sys import stdout
from os import path
import warnings 

# Flag indicating if debugging output will be displayed.
debug = True

#Flag indicating if a topology file update is needed
topFileUpdateNeeded = False

# Regular expression string utilized to help parse qstat output.
qstatRegEx = 'yra[^/*]*'

def getRawAllocatedNodesString():
    if os.environ.has_key('PBS_JOBID'):
        #Get basic qstat information and force output of allocated nodes to be
        #on the same line as the job ID.
        qstatnodeinfo = commands.getoutput('qstat -f $PBS_JOBID -n1')
        if debug:
            print ' '
            #print qstatnodeinfo
        #Last item in list should always be a string containing a list of 
        #allocated nodes in the form: 'yra051/7+yra051/6+yra051...
        #yra051/0+yra087/7+yra087...yra087/0
    else:
        print 'fatal error...PBS_JOBID not defined.'
        sys.exit()
    return qstatnodeinfo.split(' ')[-1]

def getAllocatedNodesString():
    regex = re.compile(qstatRegEx)
    dupnodeslist = regex.findall(getRawAllocatedNodesString())
    
    #Return string without duplicate node entries.
    nodelist = list(Set(dupnodeslist))
    
    #Append .lanl.gov
    """
	for i in range(len(nodeslist)):
        nodeslist[i] += '.lanl.gov'
    """
    # Not sure if sort is needed...
    nodelist.sort()
    return string.join(nodelist)

def prepENV(topologyStringHash):
    global topFileUpdateNeeded
    
    if debug:
        sys.stdout.write('checking for OPENSS_MRNET_TOPOLOGY_FILE...')
    if os.environ.has_key('OPENSS_MRNET_TOPOLOGY_FILE'):
        if debug:
            print 'defined'
            sys.stdout.write('topology update needed...')
        
        #Get topology file path for redefinition of OPENSS_MRNET_TOPOLOGY_FILE.
        #If OPENSS_MRNET_TOPOLOGY_FILE is defined, assume that user would like
        #all OpenSpeedShop-related topology files created in the same directory.
        usertoproot = os.path.dirname(os.environ['OPENSS_MRNET_TOPOLOGY_FILE'])

        #Overwrite OPENSS_MRNET_TOPOLOGY_FILE with:
        #/user/defined/top/path/HOSTNAME.<topologyStringHash>.top
        newtopenv = usertoproot + os.sep + os.uname()[1].split('.')[0] + \
        '.' + topologyStringHash + '.top'
        
        os.environ['OPENSS_MRNET_TOPOLOGY_FILE'] = newtopenv
    else:
        if debug:
            print 'not defined'
            sys.stdout.write('topology update needed...')

        #If OPENSS_MRNET_TOPOLOGY_FILE is not defined, 
        #then default to $HOME/HOSTNAME.<topologyStringHash>.top
        os.environ['OPENSS_MRNET_TOPOLOGY_FILE'] = \
        os.environ['HOME'] + os.sep + os.uname()[1].split('.')[0] + \
        '.' + topologyStringHash + '.top'

    if os.path.isfile(os.environ['OPENSS_MRNET_TOPOLOGY_FILE']):
        if debug:
            print 'no'
    else:
        if debug:
            print 'yes'
        topFileUpdateNeeded = True
    if debug:
        print ('OPENSS_MRNET_TOPOLOGY_FILE: ' + \
        os.environ['OPENSS_MRNET_TOPOLOGY_FILE'])

## haveTopgen()
# Returns True if mrnet_topgen is present in $OPENSS_PREFIX/bin.
# Returns False otherwise.
def haveTopgen():
    return os.path.isfile(os.environ['OPENSS_PREFIX'] + os.sep + 'bin' + \
                        os.sep + 'mrnet_topgen')

#FIXME
## generateMRNetTopologyString(degree, numleaves)
# Returns mrnet_topgen-based MRNet topology string.
def generateMRNetTopologyString(degree, numleaves):
    mrntstr = 'echo "' + getAllocatedNodesString() + '" | ' + \
				'mrnet_topgen -b %dx%d' % (degree, numleaves)
    
    #Capture generated MRNet topology string
    mrntopstr = commands.getoutput(mrntstr)
    
    if debug:
        print mrntopstr

    return mrntopstr
    
def createTopologyFile(topologyString):
    #Make certain OPENSS_MRNET_TOPOLOGY_FILE is present
    if os.environ.has_key('OPENSS_MRNET_TOPOLOGY_FILE'):
        try:
            topfile = open(os.environ['OPENSS_MRNET_TOPOLOGY_FILE'], 'w')
            topfile.write(topologyString)
            topfile.close()
        except:
            exc_info = sys.exc_info()
            print exc_info[1]
            print ('an error was encountered during MRNet topology file ' +
            'generation...')
            sys.exit()
    else:
        print ('OPENSS_MRNET_TOPOLOGY_FILE environment variable ' +
        'not defined...')
        sys.exit()
    

def getAllocatedNodeCount():
    rlnodeinfo = commands.getoutput('qstat -f $PBS_JOBID | ' + 
    'grep Resource_List.nodes')
    return int(rlnodeinfo.split(' ')[-1].split(':')[0])
     
def getAllocatedNodePPNCount():
    rlnodeinfo = commands.getoutput('qstat -f $PBS_JOBID | ' +
    'grep Resource_List.nodes')
    
    return int(rlnodeinfo.split(' ')[-1].split('=')[-1])

##generateSimpleTopologyString() 
def generateSimpleTopologyString():
    #Strip .lanl.gov
    hostname = os.uname()[1]
    hostname = hostname.split('.')[0]
    
    return hostname + ':0 => \n' + '  ' + hostname + ':1 ;'

#TODO:FIXME 
def generateSimpleBETopologyString():
    nodelist = getAllocatedNodesString().split(' ')
    
    topstring = nodelist[0] + ':0 =>\n  ' + nodelist[0] + ':1'

    for node in nodelist[1::1]:
        topstring += '\n  ' + node + ':0'
    
    topstring += ' ;'
    return topstring

# Overkill
def getStringHashValue(inputString):
    return hex(hash(inputString))

##main()
def main():
    #Assuming presence of PBS_JOBID is a good 
    #indicator that we are on compute nodes
    if os.environ.has_key('PBS_JOBID'):
        if debug:
            print 'on compute node...'
        prepENV(getStringHashValue(generateSimpleBETopologyString()))
        print generateSimpleBETopologyString()
        #TODO:FIXME Simple hack to get things going
        if(topFileUpdateNeeded):
            createTopologyFile(generateSimpleBETopologyString())
    #If PBS_JOBID is not present, then we
    #better be on a compile node...
    else:
        if debug:
            print 'on compile node...'
        #Make sure we have mrnet_topgen before we continue. 
        #It's not used here, but will be.??
        prepENV(getStringHashValue(generateSimpleTopologyString()))
        print generateSimpleTopologyString()
		#TODO: FIXME Simple hack to get things going
        if(topFileUpdateNeeded):
            createTopologyFile(generateSimpleTopologyString())

if __name__ == '__main__' :
    #Used to suppress python hex() Future Warning message.
    warnings.filterwarnings('ignore')
    main()
