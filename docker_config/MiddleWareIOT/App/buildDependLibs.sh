#!/bin/bash


operation_so() {
    local dirCopy="$1"   
    local dirPaste="$2"

    for archivo in "$dirCopy"/*".so"*; do
        if [ -f "$archivo" ]; then
        	echo "cp $archivo $dirPaste"
		    cp "$archivo" "$dirPaste"
        	#Puedes realizar acciones adicionales aquí, si es necesario
    	fi
    done
}



qtDirLib="/opt/Qt/6.2.0/gcc_64/lib"

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


qtCoreLib="$qtDirLib/libQt6Core.so.6"
if [ -f "$qtCoreLib" ]; then
    echo "Copy libQt6Core.so.6"
    cp "$qtCoreLib" "$dirPaste"
else
    echo "Error: libQt6Core.so.6 no encontrado en $qtDirLib"
fi


#Pluigns

'
basicStatisticsLibDir="/Plugins/Interface/Plugins/BasicStatistics/BuildGCC11/debug"
dirCopy="$projectDir$basicStatisticsLibDir"
echo "Copy BasicStatistics Libs"
operation_so "$dirCopy" "$dirPaste"


fftAnalysisLibDir="/Plugins/Interface/Plugins/FFTAnalysis/BuildGCC11/debug"
dirCopy="$projectDir$fftAnalysisLibDir"
echo "Copy FFTAnalysis Libs"
operation_so "$dirCopy" "$dirPaste"


mqttPublishLibDir="/Plugins/Interface/Plugins/MQTTPublish/BuildGCC11/debug"
dirCopy="$projectDir$mqttPublishLibDir"
echo "Copy MQTTPublish Libs"
operation_so "$dirCopy" "$dirPaste"


mqttSubscriberLibDir="/Plugins/Interface/Plugins/MQTTSubscriber/BuildGCC11/debug"
dirCopy="$projectDir$mqttSubscriberLibDir"
echo "Copy MQTTSubscriber Libs"
operation_so "$dirCopy" "$dirPaste"


unitConverterLibDir="/Plugins/Interface/Plugins/UnitConverter/BuildGCC11/debug"
dirCopy="$projectDir$unitConverterLibDir"
echo "Copy UnitConverter Libs"
operation_so "$dirCopy" "$dirPaste"
'