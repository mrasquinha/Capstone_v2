bin_PROGRAMS = simMc2Mesh_debug simMc2Mesh_profile simMc2Mesh

noinst_LIBRARIES = libIris_debug.a libIris_profile.a libIris.a

OBJDIR = $(TOPDIR)/build
BUILDDIR = $(TOPDIR)/build
CXX_FLAGS = -D_FILE_OFFSET_BITS=64 -I source -pthread -ansi -Wall -g -gstabs+ -O3 -static -static-libgcc
CXXLD = g++ -static -lgc -lc
CXXLD_PROFILE = g++ -lgcov -static -lgc -lc
#DEBUG_FLAGS = -D_DEBUG -D_DEBUG_ROUTER 
DEBUG_FLAGS = -g -pg -D_STLP_DEBUG -D_DEBUG -DDEBUG -D_DEBUG_ROUTER -D_DEBUG_INTERFACE -DDEBUG
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage -lgcov -g -pg
IRIS_SOURCES = \
		  source/kernel/link.cc \
		  source/kernel/simulator.cc \
		  source/kernel/component.cc \
		  source/data_types/impl/irisEvent.cc \
		  source/data_types/impl/flit.cc \
		  source/data_types/impl/util.cc \
		  source/data_types/impl/highLevelPacket.cc \
		  source/data_types/impl/lowLevelPacket.cc \
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
		  source/components/impl/genericVcArbiter.cc \
		  source/components/impl/genericLink.cc \
		  source/components/impl/pvtopv_swa.cc \
		  source/components/impl/ptop_swa.cc \
		  source/components/impl/genericRouterNoVcs.cc \
		  source/components/impl/genericRouterVct.cc \
		  source/components/impl/genericFlatMc.cc \
		  source/components/impl/genericTPG.cc \
		  source/MemCtrl/addr_map.cc \
		  source/MemCtrl/request.cc \
		  source/MemCtrl/request_handler.cc \
		  source/MemCtrl/channel_handler.cc \
		  source/MemCtrl/rank_handler.cc \
		  source/MemCtrl/bank_handler.cc \
		  source/MemCtrl/bus_handler.cc \
		  source/MemCtrl/cmd_issuer.cc \
		  source/MemCtrl/bus.cc \
		  source/MemCtrl/data_bus_handler.cc \
		  source/MemCtrl/cmd_bus_handler.cc \
		  source/MemCtrl/dram.cc \
		  source/MemCtrl/refresh_manager.cc \
		  source/MemCtrl/response_handler.cc \
		  source/MemCtrl/stats.cc \
		  source/MemCtrl/MC.cc \
		  source/MemCtrl/mshr.cc \
		  source/MemCtrl/NI.cc \
		  source/frontend/impl/mesh.cc 


## simMc2Mesh
simMc2Mesh_CXXFLAGS = $(CXX_FLAGS)

simMc2Mesh_SOURCES = \
	       source/frontend/impl/simMc2Mesh.cc
simMc2Mesh_LDADD = libIris.a

## simMc2Mesh_debug
simMc2Mesh_debug_CXXFLAGS = $(CXX_FLAGS) 

simMc2Mesh_debug_SOURCES = \
	       source/frontend/impl/simMc2Mesh.cc
simMc2Mesh_debug_LDADD = libIris_debug.a

## simMc2Mesh_profile
simMc2Mesh_profile_CXXFLAGS = $(CXX_FLAGS) $(DEBUG_FLAGS) $(PROFILE_FLAGS)

simMc2Mesh_profile_SOURCES = \
	       source/frontend/impl/simMc2Mesh.cc
simMc2Mesh_profile_LDADD = libIris_profile.a

##libIris
libIris_a_CXXFLAGS = $(CXX_FLAGS)
libIris_a_SOURCES = $(IRIS_SOURCES)

##libIris_debug
libIris_debug_a_CXXFLAGS = $(CXX_FLAGS) $(DEBUG_FLAGS)
libIris_debug_a_SOURCES = $(IRIS_SOURCES)

##libIris_profile
libIris_profile_a_CXXFLAGS = $(CXX_FLAGS) $(DEBUG_FLAGS) $(PROFILE_FLAGS)
libIris_profile_a_SOURCES = $(IRIS_SOURCES)

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
		 source/components/impl/genericVcArbiter.h \
		 source/components/impl/genericLink.h \
		 source/components/impl/pvtopv_swa.h \
		 source/components/impl/ptop_swa.h \
		 source/components/impl/genericRouterNoVcs.h \
		 source/components/impl/genericRouterVct.h \
		 source/components/impl/genericTPG.h \
		 source/components/impl/genericFlatMc.h \
		 source/frontend/impl/mesh.h \
		 source/MemCtrl/constants.h \
		 source/MemCtrl/addr_map.h \
		 source/MemCtrl/request.h \
		 source/MemCtrl/request_handler.h \
		 source/MemCtrl/channel_handler.h \
		 source/MemCtrl/rank_handler.h \
		 source/MemCtrl/bank_handler.h \
		 source/MemCtrl/bus_handler.h \
		 source/MemCtrl/cmd_issuer.h \
		 source/MemCtrl/bus.h \
		 source/MemCtrl/data_bus_handler.h \
		 source/MemCtrl/cmd_bus_handler.h \
		 source/MemCtrl/dram.h \
		 source/MemCtrl/refresh_manager.h \
		 source/MemCtrl/response_handler.h \
		 source/MemCtrl/stats.h \
		 source/MemCtrl/MC.h \
		 source/MemCtrl/mshr.h \
		 source/MemCtrl/NI.h
