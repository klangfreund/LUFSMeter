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

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "LUFSMETER_STANDALONE=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.3" -D "JUCE_APP_VERSION_HEX=0x3" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../../libraries/juce/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "LUFSMETER_STANDALONE=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.3" -D "JUCE_APP_VERSION_HEX=0x3" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../../libraries/juce/modules
  TARGET := LUFSMeterStandalone
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

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "LUFSMETER_STANDALONE=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.3" -D "JUCE_APP_VERSION_HEX=0x3" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../../libraries/juce/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "LUFSMETER_STANDALONE=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.3" -D "JUCE_APP_VERSION_HEX=0x3" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../../libraries/juce/modules
  TARGET := LUFSMeterStandalone
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/Ebu128LoudnessMeter_1d98716d.o \
  $(OBJDIR)/SecondOrderIIRFilter_dcd27f22.o \
  $(OBJDIR)/BackgroundGrid_71860066.o \
  $(OBJDIR)/BackgroundGridCaption_b3231aaa.o \
  $(OBJDIR)/BackgroundVerticalLinesAndCaption_4ed3b182.o \
  $(OBJDIR)/LoudnessBar_bfbc8f62.o \
  $(OBJDIR)/LoudnessBarRangeSlider_b3e9cd46.o \
  $(OBJDIR)/LoudnessHistory_8a3263.o \
  $(OBJDIR)/LoudnessHistoryGroup_2bb7fea6.o \
  $(OBJDIR)/LoudnessNumeric_efac845c.o \
  $(OBJDIR)/LoudnessRangeBar_4a58eb71.o \
  $(OBJDIR)/LoudnessRangeHistory_ee6beef2.o \
  $(OBJDIR)/MultiChannelLoudnessBar_40cd37f8.o \
  $(OBJDIR)/PreferencesPane_b62376b8.o \
  $(OBJDIR)/AnimatedSidePanel_46aaab02.o \
  $(OBJDIR)/LUFSMeterAudioProcessor_483d57b.o \
  $(OBJDIR)/LUFSMeterAudioProcessorEditor_9743a808.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_f44f7272.o \
  $(OBJDIR)/juce_audio_devices_a3e7f2b0.o \
  $(OBJDIR)/juce_audio_formats_d2693c50.o \
  $(OBJDIR)/juce_audio_processors_be2bba2a.o \
  $(OBJDIR)/juce_audio_utils_159d6270.o \
  $(OBJDIR)/juce_core_c89f1f54.o \
  $(OBJDIR)/juce_data_structures_3dd51c10.o \
  $(OBJDIR)/juce_events_3829c1c8.o \
  $(OBJDIR)/juce_graphics_76087d2c.o \
  $(OBJDIR)/juce_gui_basics_13716ea8.o \
  $(OBJDIR)/juce_gui_extra_392f2a30.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking LUFSMeterStandalone
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning LUFSMeterStandalone
	@$(CLEANCMD)

strip:
	@echo Stripping LUFSMeterStandalone
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/Ebu128LoudnessMeter_1d98716d.o: ../../../LUFSMeter/Source/Ebu128LoudnessMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Ebu128LoudnessMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SecondOrderIIRFilter_dcd27f22.o: ../../../LUFSMeter/Source/filters/SecondOrderIIRFilter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SecondOrderIIRFilter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BackgroundGrid_71860066.o: ../../../LUFSMeter/Source/gui/BackgroundGrid.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BackgroundGrid.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BackgroundGridCaption_b3231aaa.o: ../../../LUFSMeter/Source/gui/BackgroundGridCaption.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BackgroundGridCaption.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BackgroundVerticalLinesAndCaption_4ed3b182.o: ../../../LUFSMeter/Source/gui/BackgroundVerticalLinesAndCaption.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BackgroundVerticalLinesAndCaption.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessBar_bfbc8f62.o: ../../../LUFSMeter/Source/gui/LoudnessBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessBarRangeSlider_b3e9cd46.o: ../../../LUFSMeter/Source/gui/LoudnessBarRangeSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessBarRangeSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessHistory_8a3263.o: ../../../LUFSMeter/Source/gui/LoudnessHistory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessHistory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessHistoryGroup_2bb7fea6.o: ../../../LUFSMeter/Source/gui/LoudnessHistoryGroup.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessHistoryGroup.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessNumeric_efac845c.o: ../../../LUFSMeter/Source/gui/LoudnessNumeric.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessNumeric.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessRangeBar_4a58eb71.o: ../../../LUFSMeter/Source/gui/LoudnessRangeBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessRangeBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LoudnessRangeHistory_ee6beef2.o: ../../../LUFSMeter/Source/gui/LoudnessRangeHistory.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LoudnessRangeHistory.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MultiChannelLoudnessBar_40cd37f8.o: ../../../LUFSMeter/Source/gui/MultiChannelLoudnessBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MultiChannelLoudnessBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PreferencesPane_b62376b8.o: ../../../LUFSMeter/Source/gui/PreferencesPane.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PreferencesPane.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AnimatedSidePanel_46aaab02.o: ../../../LUFSMeter/Source/gui/AnimatedSidePanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AnimatedSidePanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LUFSMeterAudioProcessor_483d57b.o: ../../../LUFSMeter/Source/LUFSMeterAudioProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LUFSMeterAudioProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LUFSMeterAudioProcessorEditor_9743a808.o: ../../../LUFSMeter/Source/LUFSMeterAudioProcessorEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LUFSMeterAudioProcessorEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_f44f7272.o: ../../../../libraries/juce/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a3e7f2b0.o: ../../../../libraries/juce/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d2693c50.o: ../../../../libraries/juce/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_be2bba2a.o: ../../../../libraries/juce/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_159d6270.o: ../../../../libraries/juce/modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
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

-include $(OBJECTS:%.o=%.d)
