# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.5.0" -D "JUCE_APP_VERSION_HEX=0x500" -I /usr/include -I /usr/include/freetype2 -I ../../../../libraries/vstsdk2.4 -I ../../JuceLibraryCode -I ../../../../libraries/juce/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.5.0" -D "JUCE_APP_VERSION_HEX=0x500" -I /usr/include -I /usr/include/freetype2 -I ../../../../libraries/vstsdk2.4 -I ../../JuceLibraryCode -I ../../../../libraries/juce/modules
  TARGET := LUFSMeter.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.5.0" -D "JUCE_APP_VERSION_HEX=0x500" -I /usr/include -I /usr/include/freetype2 -I ../../../../libraries/vstsdk2.4 -I ../../JuceLibraryCode -I ../../../../libraries/juce/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.5.0" -D "JUCE_APP_VERSION_HEX=0x500" -I /usr/include -I /usr/include/freetype2 -I ../../../../libraries/vstsdk2.4 -I ../../JuceLibraryCode -I ../../../../libraries/juce/modules
  TARGET := LUFSMeter.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/Ebu128LoudnessMeter_8fc054c2.o \
  $(OBJDIR)/SecondOrderIIRFilter_223c8b6d.o \
  $(OBJDIR)/AnimatedSidePanel_ce670d17.o \
  $(OBJDIR)/BackgroundGrid_9d9de71.o \
  $(OBJDIR)/BackgroundGridCaption_63066a3f.o \
  $(OBJDIR)/BackgroundVerticalLinesAndCaption_837b4997.o \
  $(OBJDIR)/LoudnessBar_dc9d6537.o \
  $(OBJDIR)/LoudnessBarRangeSlider_707051.o \
  $(OBJDIR)/LoudnessHistory_72b215b8.o \
  $(OBJDIR)/LoudnessHistoryGroup_e711e871.o \
  $(OBJDIR)/LoudnessNumeric_61d467b1.o \
  $(OBJDIR)/LoudnessRangeBar_1d2d72bc.o \
  $(OBJDIR)/LoudnessRangeHistory_a9c5d8bd.o \
  $(OBJDIR)/MultiChannelLoudnessBar_851af64d.o \
  $(OBJDIR)/PreferencesPane_284b5a0d.o \
  $(OBJDIR)/LUFSMeterAudioProcessor_8eb00650.o \
  $(OBJDIR)/LUFSMeterAudioProcessorEditor_ff1b251d.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_f44f7272.o \
  $(OBJDIR)/juce_audio_processors_be2bba2a.o \
  $(OBJDIR)/juce_core_c89f1f54.o \
  $(OBJDIR)/juce_data_structures_3dd51c10.o \
  $(OBJDIR)/juce_events_3829c1c8.o \
  $(OBJDIR)/juce_graphics_76087d2c.o \
  $(OBJDIR)/juce_gui_basics_13716ea8.o \
  $(OBJDIR)/juce_gui_extra_392f2a30.o \
  $(OBJDIR)/juce_PluginUtilities_6248d5bc.o \
  $(OBJDIR)/juce_VST3_Wrapper_762448c3.o \
  $(OBJDIR)/juce_VST_Wrapper_fc622cc5.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking LUFSMeter
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning LUFSMeter
	@$(CLEANCMD)

strip:
	@echo Stripping LUFSMeter
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/Ebu128LoudnessMeter_8fc054c2.o: ../../Source/Ebu128LoudnessMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Ebu128LoudnessMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SecondOrderIIRFilter_223c8b6d.o: ../../Source/filters/SecondOrderIIRFilter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SecondOrderIIRFilter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AnimatedSidePanel_ce670d17.o: ../../Source/gui/AnimatedSidePanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AnimatedSidePanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BackgroundGrid_9d9de71.o: ../../Source/gui/BackgroundGrid.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BackgroundGrid.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BackgroundGridCaption_63066a3f.o: ../../Source/gui/BackgroundGridCaption.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BackgroundGridCaption.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BackgroundVerticalLinesAndCaption_837b4997.o: ../../Source/gui/BackgroundVerticalLinesAndCaption.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BackgroundVerticalLinesAndCaption.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessBar_dc9d6537.o: ../../Source/gui/LoudnessBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessBarRangeSlider_707051.o: ../../Source/gui/LoudnessBarRangeSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessBarRangeSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessHistory_72b215b8.o: ../../Source/gui/LoudnessHistory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessHistory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessHistoryGroup_e711e871.o: ../../Source/gui/LoudnessHistoryGroup.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessHistoryGroup.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessNumeric_61d467b1.o: ../../Source/gui/LoudnessNumeric.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessNumeric.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessRangeBar_1d2d72bc.o: ../../Source/gui/LoudnessRangeBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessRangeBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessRangeHistory_a9c5d8bd.o: ../../Source/gui/LoudnessRangeHistory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessRangeHistory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MultiChannelLoudnessBar_851af64d.o: ../../Source/gui/MultiChannelLoudnessBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MultiChannelLoudnessBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PreferencesPane_284b5a0d.o: ../../Source/gui/PreferencesPane.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PreferencesPane.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LUFSMeterAudioProcessor_8eb00650.o: ../../Source/LUFSMeterAudioProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LUFSMeterAudioProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LUFSMeterAudioProcessorEditor_ff1b251d.o: ../../Source/LUFSMeterAudioProcessorEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LUFSMeterAudioProcessorEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_f44f7272.o: ../../../../libraries/juce/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_be2bba2a.o: ../../../../libraries/juce/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_c89f1f54.o: ../../../../libraries/juce/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_3dd51c10.o: ../../../../libraries/juce/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_3829c1c8.o: ../../../../libraries/juce/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_76087d2c.o: ../../../../libraries/juce/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_13716ea8.o: ../../../../libraries/juce/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_392f2a30.o: ../../../../libraries/juce/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_6248d5bc.o: ../../../../libraries/juce/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST3_Wrapper_762448c3.o: ../../../../libraries/juce/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST3_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_fc622cc5.o: ../../../../libraries/juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
