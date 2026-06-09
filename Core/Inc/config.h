/**
  * Created on: Jun 7, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : config.h
  * @brief          : project level configs
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#ifndef CORE_INC_CONFIG_H_
#define CORE_INC_CONFIG_H_

#ifdef CORE_INC_CONFIG_C_
#define _DECL
#define _INIT(...) = __VA_ARGS__
#else
#define _DECL extern
#define _INIT(...)
#endif /* CORE_INC_CONFIG_C_ */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h> /* uintx_t types */
#include <stdbool.h> /* bools 'un-needed' but makes it a little easier to read */

/* Non Hal Hardware configs */
#define ANALOG_VOLTAGE_REFERENCE 3.3

/* Versioning ----------------------------------------------------------------*/
/* TODO: make build script/ cmake pass in version info bassed on tags/ branch name */
#ifndef BUILD_VER_DEBUG
#define BUILD_VER_DEBUG   true
#endif

#ifndef BUILD_VER_VARIANT
#define BUILD_VER_VARIANT variant_main 
#endif

#ifndef BUILD_VER_MAJOR
#define BUILD_VER_MAJOR   0
#endif

#ifndef BUILD_VER_MINOR
#define BUILD_VER_MINOR   0
#endif

#ifndef BUILD_VER_BUILD
#define BUILD_VER_BUILD   0
#endif

/* usefull for ensuring test builds/ unrealeased versions don't leave engineering */
#define VARIANT_DEBUG_MASK 0x80

/* allows variant builds to both be easily identified and not require mutually exclusive ver# */
typedef enum : uint8_t {
	/*reaserved debug mask = 0x80*/
	/*variant_   = 0x70,*/	
	/*variant_   = 0x60,*/	
	/*variant_   = 0x50,*/	
	/*variant_   = 0x40,*/	
	/*variant_   = 0x30,*/	
	/*variant_   = 0x20,*/
	/*variant_   = 0x10,*/
	/*variant_   = 0x08,*/	
	/*variant_   = 0x07,*/	
	/*variant_   = 0x06,*/	
	/*variant_   = 0x05,*/	
	/*variant_   = 0x04,*/	
	/*variant_   = 0x03,*/	
	/*variant_   = 0x02,*/	
	variant_main = 0x01	
}Variants;

typedef struct {
	Variants variant;
	uint16_t major;
	uint16_t minor;
	uint16_t build;
} Version_t;

/* version info placed at head of build to make it easy to verify build info
 * leading 0xDEADBEEF for quick search, split words as build seems to be LSW (DEAD and BEEF were swapped in hexdump)*/
_DECL volatile const uint16_t version_search_header_MSW __attribute__((section(".versioning"))) _INIT( 0xDEAD );
_DECL volatile const uint16_t version_search_header_LSW __attribute__((section(".versioning"))) _INIT( 0xBEEF );
_DECL volatile const Version_t VERSION_INFO __attribute__((section(".versioning")))             _INIT( {
	/* build variant id bitwise or'd with the debug flag if BUILD_VER_DEBUG is non zero */
	.variant = BUILD_VER_VARIANT | (BUILD_VER_DEBUG) ? VARIANT_DEBUG_MASK : 0x00,
	.major   = BUILD_VER_MAJOR,
	.minor   = BUILD_VER_MINOR,
	.build   = BUILD_VER_BUILD
});

#undef _DECL
#undef _INIT
#endif /* CORE_INC_CONFIG_H_ */
