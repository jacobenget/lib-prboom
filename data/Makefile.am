#
# Install, and make if needed, prboom.wad
#

waddir=$(DOOMWADDIR)
wad_DATA=prboom.wad
EXTRA_DIST=prboom.wad prboom.txt
MAINTAINERCLEANFILES=prboom.wad

$(builddir)/prboom.wad: $(srcdir)/prboom.txt $(wildcard $(srcdir)graphics/*.ppm $(srcdir)sprites/*.ppm $(srcdir)lumps/*.lmp $(srcdir)sounds/*.wav)
	-rm -f $@
	cd $(srcdir); DOOMWADDIR=$(DOOMWADDIR) deutex -make prboom.txt $(abs_builddir)/$@
