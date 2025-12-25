###############################################################################
#####               This makefile generates ELWWD.DLL                     #####
###############################################################################
!include $(WGDEV)\src\gcrules.mak

!if $(OS) == WNT
DLLLIB =          \
     $(DLLLIB)    \
     wgserver.lib \
     galme.lib    \
     galgsbl.lib
MATHDLL =
DEFILE =

!endif

!if $(OS) == WG2
PARSEOPTS = ${PARSEOPTS} -w-use
DLLLIB = $(DLLLIB) wgserver.lib galgsbl.lib galme.lib $(BORLAND)\lib\mathh.lib ${DOSEXT}\bc4\lib\phapi.lib
MATHDLL = $(DOSEXT)\bc4\lib\fpdmy
DEFILE = $(WGLIBDIR)\mathdef.def

!endif

OBJFILES =          \
     $(TEMPDIR)\elwwdglb.obj \
     $(TEMPDIR)\elwwdrfx.obj \
     $(TEMPDIR)\elwwdmap.obj \
     $(TEMPDIR)\elwwd3d.obj  \
     $(TEMPDIR)\elwwdans.obj \
     $(TEMPDIR)\elwwdrou.obj \
     $(TEMPDIR)\elwwdfsd.obj \
     $(TEMPDIR)\elwwdinn.obj \
     $(TEMPDIR)\elwwdrip.obj \
     $(TEMPDIR)\elwwdgld.obj \
     $(TEMPDIR)\elwwdenc.obj \
     $(TEMPDIR)\elwwdshp.obj \
     $(TEMPDIR)\elwwd.obj

start:              \
     $(GCBUILD)     \
     elwwd.dll    

elwwd.dll:          \
     $(OBJFILES)    \
     $(DLLLIB)      \
     $(DEFILE)      \
     $(VIRFILES)
     $(LINK) $(LIBCMD) @&&|
$(PRODLL) ${MATHDLL} $(OBJFILES)
$(RUNDIR)\$&
$(RUNDIR)\$&
$(DLLLIB) $(LINKDLL)
$(DEFILE)
|
