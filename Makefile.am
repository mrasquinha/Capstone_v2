AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = simMc2Mesh_debug

noinst_LIBRARIES = libIris.a libIris_debug.a

OBJDIR = $(TOPDIR)/build
BUILDDIR = $(TOPDIR)/build
CXX_FLAGS = -D_STLP_DEBUG -I source -pthread -ansi -Wall -g -gstabs+ -O0 -fkeep-inline-functions -fpermissive
DEBUG_FLAGS = -D_DEBUG -D_DEBUG_ROUTER 
#DEBUG_FLAGS = -D_DEBUG -D_DEBUG_ROUTER -D_DEBUG_INTERFACE
IRIS_SOURCES = \
		  source/kernel/link.cc \
		  source/kernel/simulator.cc \
		  source/kernel/component.cc \
		  source/data_types/impl/irisEvent.cc \
		  source/data_types/impl/flit.cc \
		  source/data_types/impl/util.cc \
		  source/data_types/impl/highLevelPacket.cc \
		  source/data_types/impl/lowLevelPacket.cc \
                  source/memctrl/request.cc \
		  source/randomNumbers/impl/libRandom.cpp \
		  source/randomNumbers/impl/rng.cpp \
		  source/randomNumbers/impl/RngStream.cpp \
		  source/components/interfaces/router.cc \
		  source/components/interfaces/processor.cc \
		  source/components/interfaces/interface.cc \
		  source/components/interfaces/irisLink.cc \
		  source/components/interfaces/networkComponent.cc \
		  source/components/impl/genericBuffer.cc \
		  source/components/impl/genericRC.cc \
		  source/components/impl/genericCrossbar.cc \
		  source/components/impl/genericInterface.cc \
		  source/components/impl/genericData.cc \
		  source/components/impl/genericArbiter.cc \
		  source/components/impl/genericSink.cc \
		  source/components/impl/genericLink.cc \
		  source/components/impl/genericPortArbiter.cc \
		  source/components/impl/myArbiter.cc \
		  source/components/impl/pvtop_swa.cc \
		  source/components/impl/genericVcArbiter.cc \
		  source/components/impl/myRouter.cc \
		  source/components/impl/genericRPG.cc \
		  source/components/impl/genericTPG.cc \
		  source/tests/packetSource.cc

## simMc2Mesh
#simMc2Mesh_CXXFLAGS = $(CXX_FLAGS)

#simMc2Mesh_SOURCES = \
#	       source/frontend/impl/simMc2Mesh.cc
#simMc2Mesh_LDADD = libIris.a

## simMc2Mesh_debug
simMc2Mesh_debug_CXXFLAGS = $(CXX_FLAGS) 

simMc2Mesh_debug_SOURCES = \
	       source/frontend/impl/simMc2Mesh.cc
simMc2Mesh_debug_LDADD = libIris_debug.a

## testRouter
#testRouter_CXXFLAGS = $(CXX_FLAGS)

#testRouter_SOURCES = \
	#	  source/tests/test4Mesh.cc

#testRouter_LDADD = libIris.a

##libIris
libIris_a_CXXFLAGS = $(CXX_FLAGS)
libIris_a_SOURCES = $(IRIS_SOURCES)

##libIris_debug
libIris_debug_a_CXXFLAGS = $(CXX_FLAGS) $(DEBUG_FLAGS)
libIris_debug_a_SOURCES = $(IRIS_SOURCES)

##Headers
noinst_HEADERS = \
		 source/kernel/simulator.h \
		 source/kernel/link.h \
		 source/kernel/component.h \
		 source/data_types/impl/irisEvent.h \
		 source/data_types/impl/flit.h \
		 source/data_types/impl/util.h \
		 source/data_types/impl/highLevelPacket.h \
		 source/data_types/impl/lowLevelPacket.h \
                 source/memctrl/request.h \
                 source/memctrl/constants.h \
		 source/randomNumbers/impl/libRandom.hpp \
		 source/randomNumbers/impl/rng.hpp \
		 source/randomNumbers/impl/RngStream.hpp \
		 source/components/interfaces/crossbar.h \
		 source/components/interfaces/addressDecoder.h \
		 source/components/interfaces/interface.h \
		 source/components/interfaces/buffer.h \
		 source/components/interfaces/outputBuffer.h \
		 source/components/interfaces/genericComponentHeader.h \
		 source/components/interfaces/virtualChannelArbiter.h \
		 source/components/interfaces/router.h \
		 source/components/interfaces/portArbiter.h \
		 source/components/interfaces/processor.h \
		 source/components/interfaces/irisLink.h \
		 source/components/interfaces/networkComponent.h \
		 source/components/impl/genericRC.h \
		 source/components/impl/genericCrossbar.h \
		 source/components/impl/genericBuffer.h \
		 source/components/impl/genericInterface.h \
		 source/components/impl/genericArbiter.h \
		 source/components/impl/genericSink.h \
		 source/components/impl/genericLink.h \
		 source/components/impl/genericPortArbiter.h \
		 source/components/impl/myArbiter.h \
		 source/components/impl/pvtop_swa.h \
		 source/components/impl/genericVcArbiter.h \
		 source/components/impl/myRouter.h \
		 source/components/impl/genericRPG.h \
		 source/components/impl/genericTPG.h \
		 source/tests/packetSource.h 
