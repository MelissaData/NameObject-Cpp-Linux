#!/bin/bash

# Name:    MelissaNameObjectLinuxCpp
# Purpose: Use the Melissa Updater to make the MelissaNameObjectLinuxCpp code usable

######################### Constants ##########################

RED='\033[0;31m' #RED
NC='\033[0m' # No Color

######################### Parameters ##########################

name=""
license=""
quiet="false"

while [ $# -gt 0 ] ; do
  case $1 in
    -n | --name) 
        name="$2" 

        if [ "$name" == "-l" ] || [ "$name" == "--license" ] || [ "$name" == "-q" ] || [ "$name" == "--quiet" ] || [ -z "$name" ];
        then
            printf "${RED}Error: Missing an argument for parameter \'name\'.${NC}\n"  
            exit 1
        fi 
        ;;
    -l | --license) 
        license="$2"

        if [ "$license" == "-q" ] || [ "$license" == "--quiet" ] || [ "$license" == "-n" ] || [ "$license" == "--name" ] || [ -z "$license" ];
        then
            printf "${RED}Error: Missing an argument for parameter \'license\'.${NC}\n"  
            exit 1
        fi   
        ;;
    -q | --quiet) 
        quiet="true" 
        ;;
  esac
  shift
done

# ######################### Config ###########################
RELEASE_VERSION='2023.04'
ProductName="DQ_NAME_DATA"

# Uses the location of the .sh file 
# Modify this if you want to use 
CurrentPath=$(pwd)
ProjectPath="$CurrentPath/MelissaNameObjectLinuxCpp"
BuildPath="$ProjectPath/Build"
DataPath="$ProjectPath/Data"

if [ ! -d $DataPath ];
then
    mkdir $DataPath
fi

if [ ! -d $BuildPath ];
then
    mkdir $BuildPath
fi

# Config variables for download file(s)
Config_FileName1="libmdName.so"
Config_ReleaseVersion1=$RELEASE_VERSION
Config_OS1="LINUX"
Config_Compiler1="GCC48"
Config_Architecture1="64BIT"
Config_Type1="BINARY"

Config_FileName2="mdNameEnums.h"
Config_ReleaseVersion2=$RELEASE_VERSION
Config_OS2="ANY"
Config_Compiler2="C"
Config_Architecture2="ANY"
Config_Type2="INTERFACE"

Config_FileName3="mdName.h"
Config_ReleaseVersion3=$RELEASE_VERSION
Config_OS3="ANY"
Config_Compiler3="C"
Config_Architecture3="ANY"
Config_Type3="INTERFACE"

# ######################## Functions #########################
DownloadDataFiles()
{
    printf "========================== MELISSA UPDATER =========================\n"
    printf "MELISSA UPDATER IS DOWNLOADING DATA FILE(S)...\n"

    ./MelissaUpdater/MelissaUpdater manifest -p $ProductName -r $RELEASE_VERSION -l $1 -t $DataPath 

    if [ $? -ne 0 ];
    then
        printf "\nCannot run Melissa Updater. Please check your license string!\n"
        exit 1
    fi     
    
    printf "Melissa Updater finished downloading data file(s)!\n"
}

DownloadSO() 
{
    printf "\nMELISSA UPDATER IS DOWNLOADING SO(s)...\n"

    # Check for quiet mode
    if [ $quiet == "true" ];
    then
        ./MelissaUpdater/MelissaUpdater file --filename $Config_FileName1 --release_version $Config_ReleaseVersion1 --license $1 --os $Config_OS1 --compiler $Config_Compiler1 --architecture $Config_Architecture1 --type $Config_Type1 --target_directory $BuildPath  &> /dev/null
        
        printf "Melissa Updater finished downloading $Config_FileName1!\n"

        ./MelissaUpdater/MelissaUpdater file --filename $Config_FileName2 --release_version $Config_ReleaseVersion2 --license $1 --os $Config_OS2 --compiler $Config_Compiler2 --architecture $Config_Architecture2 --type $Config_Type2 --target_directory $ProjectPath  &> /dev/null
        
        printf "Melissa Updater finished downloading $Config_FileName2!\n"

        ./MelissaUpdater/MelissaUpdater file --filename $Config_FileName3 --release_version $Config_ReleaseVersion3 --license $1 --os $Config_OS3 --compiler $Config_Compiler3 --architecture $Config_Architecture3 --type $Config_Type3 --target_directory $ProjectPath  &> /dev/null
        
        printf "Melissa Updater finished downloading $Config_FileName3!\n"

        if [ $? -ne 0 ];
        then
            printf "\nCannot run Melissa Updater. Please check your license string!\n"
            exit 1
        fi
    else
        ./MelissaUpdater/MelissaUpdater file --filename $Config_FileName1 --release_version $Config_ReleaseVersion1 --license $1 --os $Config_OS1 --compiler $Config_Compiler1 --architecture $Config_Architecture1 --type $Config_Type1 --target_directory $BuildPath  
        
        printf "Melissa Updater finished downloading $Config_FileName1!\n"
        
        ./MelissaUpdater/MelissaUpdater file --filename $Config_FileName2 --release_version $Config_ReleaseVersion2 --license $1 --os $Config_OS2 --compiler $Config_Compiler2 --architecture $Config_Architecture2 --type $Config_Type2 --target_directory $ProjectPath  
        
        printf "Melissa Updater finished downloading $Config_FileName2!\n"
        
        ./MelissaUpdater/MelissaUpdater file --filename $Config_FileName3 --release_version $Config_ReleaseVersion3 --license $1 --os $Config_OS3 --compiler $Config_Compiler3 --architecture $Config_Architecture3 --type $Config_Type3 --target_directory $ProjectPath  

        printf "Melissa Updater finished downloading $Config_FileName3!\n"

        if [ $? -ne 0 ];
        then
            printf "\nCannot run Melissa Updater. Please check your license string!\n"
            exit 1
        fi
    fi
}

CheckSOs() 
{
    printf "\nDouble checking SO file(s) were downloaded...\n"
    FileMissing=0
    if [ ! -f $BuildPath/$Config_FileName1 ];
    then
        printf "\n$Config_FileName1 not found\n"
        FileMissing=1
    fi
    if [ ! -f $ProjectPath/$Config_FileName2 ];
    then
        printf "\n$Config_FileName2 not found\n"
        FileMissing=1
    fi
    if [ ! -f $ProjectPath/$Config_FileName3 ];
    then
        printf "\n$Config_FileName3 not found\n"
        FileMissing=1
    fi

    if [ $FileMissing -eq 1 ];
    then
        printf "\nMissing the above data file(s).  Please check that your license string and directory are correct."
        echo 0
    else
        echo 1
    fi
}

########################## Main ############################
printf "\n======================== Melissa Name Object =======================\n                       [ C++ | Linux | 64BIT ]\n"
printf "\n=========================== BUILD PROJECT ==========================\n"
# Get license (either from parameters or user input)
if [ -z "$license" ];
then
  printf "Please enter your license string: "
  read license
fi

# Check for License from Environment Variables 
if [ -z "$license" ];
then
  license=`echo $MD_LICENSE` 
fi

if [ -z "$license" ];
then
  printf "\nLicense String is invalid!\n"
  exit 1
fi

# Use Melissa Updater to download data file(s) 
# Download data file(s) 
DownloadDataFiles $license      # comment out this line if using DQS Release

# Set data file(s) path
#DataPath=""      # uncomment this line and change to your DQS Release data file(s) directory 

#if [ ! -d $DataPath ]; # uncomment this section of code if you are using your own DQS Release data file(s) directory
#then
    #printf "\nData path is invalid!\n"
    #exit 1
#fi

# Download SO(s)
DownloadSO $license 

# Check if all SO(s) have been downloaded. Exit script if missing
SOsAreDownloaded=$(CheckSOs)

if echo "$SOsAreDownloaded" | grep -q "0";
then
    echo "$SOsAreDownloaded" | sed 's/0$//'
    printf "\nAborting program, see above.\n"
    exit 1
fi

printf "\nAll file(s) have been downloaded/updated!\n"

# Start program
# Build project
printf "\n=========================== BUILD PROJECT ==========================\n"

# Setting the path to the lib in the makefile
LibPath=`grep 'LDFLAGS = ' $ProjectPath/makefile`
NewLibPath="LDFLAGS = -L$ProjectPath/Build"

sed -i -e "s|$LibPath|$NewLibPath|g" $ProjectPath/makefile

# Generate the executable file
cd MelissaNameObjectLinuxCpp
make &> /dev/null
cd ..

# Export the path to the lib so that the executable knows where to look
export LD_LIBRARY_PATH=$BuildPath

# Run project
if [ -z "$name" ];
then
    $BuildPath/MelissaNameObjectLinuxCpp --license $license  --dataPath $DataPath
else
    $BuildPath/MelissaNameObjectLinuxCpp --license $license  --dataPath $DataPath --name "$name"
fi
