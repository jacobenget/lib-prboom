
// no color mapping
#define R_DRAWCOLUMN_FUNCNAME R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_PointUV)
#define R_DRAWCOLUMN_PIPELINE (R_DRAWCOLUMN_PIPELINE_BASE | RDC_NOCOLMAP)
#include "r_drawcolumn.inl"

// simple depth color mapping
#define R_DRAWCOLUMN_FUNCNAME R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_PointUV_PointZ)
#define R_DRAWCOLUMN_PIPELINE R_DRAWCOLUMN_PIPELINE_BASE
#include "r_drawcolumn.inl"

// z-dither
#define R_DRAWCOLUMN_FUNCNAME R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_PointUV_LinearZ)
#define R_DRAWCOLUMN_PIPELINE (R_DRAWCOLUMN_PIPELINE_BASE | RDC_DITHERZ)
#include "r_drawcolumn.inl"

// bilinear with no color mapping
#define R_DRAWCOLUMN_FUNCNAME R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_LinearUV)
#define R_DRAWCOLUMN_PIPELINE                                                  \
  (R_DRAWCOLUMN_PIPELINE_BASE | RDC_BILINEAR | RDC_NOCOLMAP)
#include "r_drawcolumn.inl"

// bilinear with simple depth color mapping
#define R_DRAWCOLUMN_FUNCNAME R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_LinearUV_PointZ)
#define R_DRAWCOLUMN_PIPELINE (R_DRAWCOLUMN_PIPELINE_BASE | RDC_BILINEAR)
#include "r_drawcolumn.inl"

// bilinear + z-dither
#define R_DRAWCOLUMN_FUNCNAME R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_LinearUV_LinearZ)
#define R_DRAWCOLUMN_PIPELINE                                                  \
  (R_DRAWCOLUMN_PIPELINE_BASE | RDC_BILINEAR | RDC_DITHERZ)
#include "r_drawcolumn.inl"

// rounded with no color mapping
#define R_DRAWCOLUMN_FUNCNAME R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_RoundedUV)
#define R_DRAWCOLUMN_PIPELINE                                                  \
  (R_DRAWCOLUMN_PIPELINE_BASE | RDC_ROUNDED | RDC_NOCOLMAP)
#include "r_drawcolumn.inl"

// rounded with simple depth color mapping
#define R_DRAWCOLUMN_FUNCNAME R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_RoundedUV_PointZ)
#define R_DRAWCOLUMN_PIPELINE (R_DRAWCOLUMN_PIPELINE_BASE | RDC_ROUNDED)
#include "r_drawcolumn.inl"

// rounded + z-dither
#define R_DRAWCOLUMN_FUNCNAME                                                  \
  R_DRAWCOLUMN_FUNCNAME_COMPOSITE(_RoundedUV_LinearZ)
#define R_DRAWCOLUMN_PIPELINE                                                  \
  (R_DRAWCOLUMN_PIPELINE_BASE | RDC_ROUNDED | RDC_DITHERZ)
#include "r_drawcolumn.inl"

#undef R_FLUSHWHOLE_FUNCNAME
#undef R_FLUSHHEADTAIL_FUNCNAME
#undef R_FLUSHQUAD_FUNCNAME
#undef R_DRAWCOLUMN_FUNCNAME_COMPOSITE
#undef R_DRAWCOLUMN_PIPELINE_BITS
