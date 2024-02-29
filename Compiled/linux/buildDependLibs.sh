#!/bin/bash


operation_so() {
    local dirCopy="$1"   
    local dirPaste="$2"

    for archivo in "$dirCopy"/*".so"*; do
        if [ -f "$archivo" ]; then
        	echo "cp $archivo $dirPaste"
		#cp "$archivo" "$dirPaste"
        	#Puedes realizar acciones adicionales aquí, si es necesario
    	fi
    done
}


projectDir="/home/cesarcherre/Projects/MiddleWareIOT"
dirCompiledLibs="/Compiled/linux/libs"
dirPaste="$projectDir$dirCompiledLibs"

managerLibDir="/Manager/DataManager/BuildGCC11/debug/DataManagerLib"
dirCopy="$projectDir$managerLibDir"
echo "Copy Manager Libs"
operation_so "$dirCopy" "$dirPaste"


mqttcommLibDir="/Communication/MQTTComm/BuildGCC11/debug/MQTTCommLib"
dirCopy="$projectDir$mqttcommLibDir"
echo "Copy MQTTComm Libs"
operation_so "$dirCopy" "$dirPaste"


mqttparserLibDir="/DataParsers/MQTTParser/BuildGCC11/debug"
dirCopy="$projectDir$mqttparserLibDir"
echo "Copy MQTTParser Libs"
operation_so "$dirCopy" "$dirPaste"


payloaderbLibDir="/DataParsers/PayloadErbessd/BuildGCC11/debug/PayloadErbessdLib"
dirCopy="$projectDir$payloaderbLibDir"
echo "Copy PayLoadErbessd Libs"
operation_so "$dirCopy" "$dirPaste"


interfaceLibDir="/Plugins/Interface/BuildGCC11/debug"
dirCopy="$projectDir$interfaceLibDir"
echo "Copy Interface Libs"
operation_so "$dirCopy" "$dirPaste"

pluginsLibDir="/Plugins/Interface/Plugins"
dirCopy="$projectDir$pluginsLibDir"
echo "Copy plugins Libs"
operation_so "$dirCopy" "$dirPaste"