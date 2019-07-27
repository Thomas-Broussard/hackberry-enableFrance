#!bin/bash

# ---------------------------------------------------------------------------------
# Name : HexGenerator
# Author : Thomas Broussard
# ---------------------------------------------------------------------------------
# Description : 
# Permet de générer tous les fichiers .hex pour la main Hackberry
#
# Remarque :
# Ne surtout pas déplacer le dossier ou son contenu ! 
# ---------------------------------------------------------------------------------

build_hex_file(){
    # params
    hackberryBoard=$1
    extensionBoard=$2

    # generer le nom du fichier
    rawOutputName=$hackberryBoard'_'$extensionBoard
    outputName=$(echo "$rawOutputName" | tr '[:upper:]' '[:lower:]')

    # 1 - modifier le fichier hackberry_mapping 
    sed -i '/#define HACKBERRY_BOARD/c\#define HACKBERRY_BOARD '$hackberryBoard'' lib/hackberry/src/hackberry_mapping.h
    sed -i '/#define EXTENSION_BOARD/c\#define EXTENSION_BOARD '$extensionBoard'' lib/hackberry/src/hackberry_mapping.h

    # 2 - compiler le fichier firmware.hex 
    ./utilities/HexGenerator/platformio.exe run --project-dir _main_program/

    # 3 - renommer le fichier .hex avec un nom adapté et le déplacer dans outputs/
    mv '_main_program/.pio/build/nanoatmega328/firmware.hex' 'hex_files/'$outputName'.hex'
    echo $outputName' successfully generated'
}


# on va au dossier racine du git
cd ../../

# on génère les fichiers requis
echo "Generate output files..."

# MK2 Board files
build_hex_file 'MK2' 'NO_EXTENSION'
build_hex_file 'MK2' 'BLUETOOTH_BOARD'


# MK3 Board files
#build_hex_file 'MK3' 'NO_EXTENSION'
#build_hex_file 'MK3' 'BLUETOOTH_BOARD'


echo "Finished"




