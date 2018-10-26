##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=pmatrix
ConfigurationName      :=Release
WorkspacePath          :=/home/domi/Documents/PROG1
ProjectPath            :=/home/domi/Documents/PROG1/pmatrix
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=domi
Date                   :=10/26/18
CodeLitePath           :=/home/domi/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="pmatrix.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Matrix_muvelet.c$(ObjectSuffix) $(IntermediateDirectory)/Matrix_IO.c$(ObjectSuffix) $(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/Matrix.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Matrix_muvelet.c$(ObjectSuffix): Matrix_muvelet.c $(IntermediateDirectory)/Matrix_muvelet.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/domi/Documents/PROG1/pmatrix/Matrix_muvelet.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Matrix_muvelet.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Matrix_muvelet.c$(DependSuffix): Matrix_muvelet.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Matrix_muvelet.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Matrix_muvelet.c$(DependSuffix) -MM Matrix_muvelet.c

$(IntermediateDirectory)/Matrix_muvelet.c$(PreprocessSuffix): Matrix_muvelet.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Matrix_muvelet.c$(PreprocessSuffix) Matrix_muvelet.c

$(IntermediateDirectory)/Matrix_IO.c$(ObjectSuffix): Matrix_IO.c $(IntermediateDirectory)/Matrix_IO.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/domi/Documents/PROG1/pmatrix/Matrix_IO.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Matrix_IO.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Matrix_IO.c$(DependSuffix): Matrix_IO.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Matrix_IO.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Matrix_IO.c$(DependSuffix) -MM Matrix_IO.c

$(IntermediateDirectory)/Matrix_IO.c$(PreprocessSuffix): Matrix_IO.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Matrix_IO.c$(PreprocessSuffix) Matrix_IO.c

$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/domi/Documents/PROG1/pmatrix/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/Matrix.c$(ObjectSuffix): Matrix.c $(IntermediateDirectory)/Matrix.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/domi/Documents/PROG1/pmatrix/Matrix.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Matrix.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Matrix.c$(DependSuffix): Matrix.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Matrix.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Matrix.c$(DependSuffix) -MM Matrix.c

$(IntermediateDirectory)/Matrix.c$(PreprocessSuffix): Matrix.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Matrix.c$(PreprocessSuffix) Matrix.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


