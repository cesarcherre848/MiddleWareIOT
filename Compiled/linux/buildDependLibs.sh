#!/bin/bash


operation_so() {
    local dirCopy="$1"   
    local dirPasteLibs="$2"

    for archivo in "$dirCopy"/*".so"*; do
        if [ -f "$archivo" ]; then
        	echo "cp $archivo $dirPasteLibs"
		    cp "$archivo" "$dirPasteLibs"
        	#Puedes realizar acciones adicionales aquí, si es necesario
    	fi
    done
}



qtDirLib="/opt/Qt/6.2.0/gcc_64/lib"

projectDir="/home/cesarcherre/Projects/MiddleWareIOT"
dirCompiledLibs="/Compiled/linux/libs"
dirPluginLibs="/Compiled/linux/plugins"
dirPasteLibs="$projectDir$dirCompiledLibs"
dirPastePluginLibs="$projectDir$dirPluginLibs"

managerLibDir="/Manager/DataManager/BuildGCC11/debug/DataManagerLib"
dirCopy="$projectDir$managerLibDir"
echo "Copy Manager Libs"
operation_so "$dirCopy" "$dirPasteLibs"


mqttcommLibDir="/Communication/MQTTComm/BuildGCC11/debug/MQTTCommLib"
dirCopy="$projectDir$mqttcommLibDir"
echo "Copy MQTTComm Libs"
operation_so "$dirCopy" "$dirPasteLibs"


mqttparserLibDir="/DataParsers/MQTTParser/BuildGCC11/debug"
dirCopy="$projectDir$mqttparserLibDir"
echo "Copy MQTTParser Libs"
operation_so "$dirCopy" "$dirPasteLibs"


payloaderbLibDir="/DataParsers/PayloadErbessd/BuildGCC11/debug/PayloadErbessdLib"
dirCopy="$projectDir$payloaderbLibDir"
echo "Copy PayLoadErbessd Libs"
operation_so "$dirCopy" "$dirPasteLibs"


interfaceLibDir="/Plugins/Interface/BuildGCC11/debug"
dirCopy="$projectDir$interfaceLibDir"
echo "Copy Interface Libs"
operation_so "$dirCopy" "$dirPasteLibs"


#Pluigns


basicStatisticsLibDir="/Plugins/Interface/Plugins/BasicStatistics/BuildGCC11/debug"
dirCopy="$projectDir$basicStatisticsLibDir"
echo "Copy BasicStatistics Libs"
operation_so "$dirCopy" "$dirPastePluginLibs"


fftAnalysisLibDir="/Plugins/Interface/Plugins/FFTAnalysis/BuildGCC11/debug"
dirCopy="$projectDir$fftAnalysisLibDir"
echo "Copy FFTAnalysis Libs"
operation_so "$dirCopy" "$dirPastePluginLibs"


mqttPublishLibDir="/Plugins/Interface/Plugins/MQTTPublish/BuildGCC11/debug"
dirCopy="$projectDir$mqttPublishLibDir"
echo "Copy MQTTPublish Libs"
operation_so "$dirCopy" "$dirPastePluginLibs"


mqttSubscriberLibDir="/Plugins/Interface/Plugins/MQTTSubscriber/BuildGCC11/debug"
dirCopy="$projectDir$mqttSubscriberLibDir"
echo "Copy MQTTSubscriber Libs"
operation_so "$dirCopy" "$dirPastePluginLibs"


unitConverterLibDir="/Plugins/Interface/Plugins/UnitConverter/BuildGCC11/debug"
dirCopy="$projectDir$unitConverterLibDir"
echo "Copy UnitConverter Libs"
operation_so "$dirCopy" "$dirPastePluginLibs"


save2DDataLibDir="/Plugins/Interface/Plugins/Save2DData/BuildGCC11/debug"
dirCopy="$projectDir$save2DDataLibDir"
echo "Copy Save2DData Libs"
operation_so "$dirCopy" "$dirPastePluginLibs"
