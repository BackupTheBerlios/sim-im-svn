sim_plugin_LTLIBRARIES = transparent.la

transparent_la_SOURCES = \
 transparent.cpp \
 transparentcfg.cpp \
 transparentcfgbase.ui \
 transtop.cpp

INCLUDES=-I../../lib $(all_includes)

transparent_la_METASOURCES = AUTO
transparent_la_LIBADD = ../../lib/libsim.la  $(LIB_QT) $(LIB_KDECORE) $(LIB_KDEUI) $(LIB_KDEFX) $(EXTRA_LIBS)
transparent_la_LDFLAGS = -module -no-undefined -avoid-version -L../../lib/.libs $(QT_LDFLAGS) $(KDE_RPATH) $(all_libraries)

install-data-hook:
	rm -rf $(DESTDIR)$(sim_plugindir)/transparent.la


