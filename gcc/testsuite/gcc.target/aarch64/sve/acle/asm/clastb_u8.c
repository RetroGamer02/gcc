/* { dg-final { check-function-bodies "**" "" "-DCHECK_ASM" } } */

#include "test_sve_acle.h"

/*
** clastb_u8_tied1:
**	clastb	z0\.b, p0, z0\.b, z1\.b
**	ret
*/
TEST_UNIFORM_Z (clastb_u8_tied1, svuint8_t,
		z0 = svclastb_u8 (p0, z0, z1),
		z0 = svclastb (p0, z0, z1))

/*
** clastb_u8_tied2:
**	mov	(z[0-9]+)\.d, z0\.d
**	movprfx	z0, z1
**	clastb	z0\.b, p0, z0\.b, \1\.b
**	ret
*/
TEST_UNIFORM_Z (clastb_u8_tied2, svuint8_t,
		z0 = svclastb_u8 (p0, z1, z0),
		z0 = svclastb (p0, z1, z0))

/*
** clastb_u8_untied:
**	movprfx	z0, z1
**	clastb	z0\.b, p0, z0\.b, z2\.b
**	ret
*/
TEST_UNIFORM_Z (clastb_u8_untied, svuint8_t,
		z0 = svclastb_u8 (p0, z1, z2),
		z0 = svclastb (p0, z1, z2))

/*
** clastb_x0_u8:
**	clastb	w0, p0, w0, z0\.b
**	ret
*/
TEST_FOLD_LEFT_X (clastb_x0_u8, uint8_t, svuint8_t,
		  x0 = svclastb_n_u8 (p0, x0, z0),
		  x0 = svclastb (p0, x0, z0))

/*
** clastb_x1_u8:
**	mov	w0, w1
**	clastb	w0, p0, w0, z0\.b
**	ret
*/
TEST_FOLD_LEFT_X (clastb_x1_u8, uint8_t, svuint8_t,
		  x0 = svclastb_n_u8 (p0, x1, z0),
		  x0 = svclastb (p0, x1, z0))
