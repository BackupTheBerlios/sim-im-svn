/*
 * xslt.h: Interfaces, constants and types related to the XSLT engine
 *
 * See Copyright for the status of this software.
 *
 * daniel@veillard.com
 */

#ifndef __XML_XSLT_H__
#define __XML_XSLT_H__

#include <libxml/tree.h>
#include "xsltexports.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * XSLT_DEFAULT_VERSION:
 *
 * The default version of XSLT supported.
 */
#define XSLT_DEFAULT_VERSION     "1.0"

/**
 * XSLT_DEFAULT_VENDOR:
 *
 * The XSLT "vendor" string for this processor.
 */
#define XSLT_DEFAULT_VENDOR      "libxslt"

/**
 * XSLT_DEFAULT_URL:
 *
 * The XSLT "vendor" URL for this processor.
 */
#define XSLT_DEFAULT_URL         "http://xmlsoft.org/XSLT/"

/**
 * XSLT_NAMESPACE:
 *
 * The XSLT specification namespace.
 */
#define XSLT_NAMESPACE ((xmlChar *) "http://www.w3.org/1999/XSL/Transform")

#if LIBXML_VERSION >= 20600
/**
 * XSLT_PARSE_OPTIONS:
 *
 * The set of options to pass to an xmlReadxxx when loading files for
 * XSLT consumption.
 */
#define XSLT_PARSE_OPTIONS \
 XML_PARSE_NOENT | XML_PARSE_DTDLOAD | XML_PARSE_DTDATTR | XML_PARSE_NOCDATA
#endif

/**
 * xsltMaxDepth:
 *
 * This value is used to detect templates loops.
 */
XSLTPUBVAR int xsltMaxDepth;

/**
 * xsltEngineVersion:
 *
 * The version string for libxslt.
 */
XSLTPUBVAR const char *xsltEngineVersion;

/**
 * xsltLibxsltVersion:
 *
 * The version of libxslt compiled.
 */
XSLTPUBVAR const int xsltLibxsltVersion;

/**
 * xsltLibxmlVersion:
 *
 * The version of libxml libxslt was compiled against.
 */
XSLTPUBVAR const int xsltLibxmlVersion;

/*
 * Global cleanup function.
 */
XSLTPUBFUN void XSLTCALL	
		xsltCleanupGlobals	(void);

#ifdef __cplusplus
}
#endif

#endif /* __XML_XSLT_H__ */
