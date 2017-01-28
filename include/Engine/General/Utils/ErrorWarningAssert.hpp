//Written by Squirrel Eiserloh

#pragma once

#ifndef include_ErrorWarningAssert
#define include_ErrorWarningAssert

#include <string>

enum eSeverityLevel {
	SEVERITY_INFORMATION,
	SEVERITY_QUESTION,
	SEVERITY_WARNING,
	SEVERITY_FATAL
};

void DebuggerPrintf( const char* messageFormat, ... );
bool IsDebuggerAvailable();
void RecoverableError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText=nullptr );
__declspec( noreturn ) void FatalError( const char* cppFileName, int cppLineNum, const std::string& errorMessage, const char* conditionText=nullptr );
void SystemDialogue_Okay( const std::string& messageTitle, const std::string& messageText, eSeverityLevel severity );
bool SystemDialogue_OkayCancel( const std::string& messageTitle, const std::string& messageText, eSeverityLevel severity );
bool SystemDialogue_YesNo( const std::string& messageTitle, const std::string& messageText, eSeverityLevel severity );
int SystemDialogue_YesNoCancel( const std::string& messageTitle, const std::string& messageText, eSeverityLevel severity );



//-----------------------------------------------------------------------------------------------
// Summary of macros
//
// #define ERROR_AND_DIE( errorMessageText )					// Show error dialogue, then shut down the app; "MUST not reach this point"
// #define ERROR_RECOVERABLE( errorMessageText )				// Show error dialogue, then proceed; "SHOULD not reach this point"
// #define GUARANTEE_OR_DIE( condition, errorMessageText )		// If condition is false, show error dialogue then shut down the app; "MUST be true"
// #define GUARANTEE_RECOVERABLE( condition, errorMessageText )	// If condition is false, show error dialogue then proceed; "SHOULD be true"
// #define ASSERT_OR_DIE( condition, errorMessageText )			// Same as GUARANTEE_OR_DIE, but removed if DISABLE_ASSERTS is #defined
// #define ASSERT_RECOVERABLE( condition, errorMessageText )	// Same as GUARANTEE_RECOVERABLE, but removed if DISABLE_ASSERTS is #defined
// 
// Most of these also have generic versions with one less parameter (no errorMessageText), but use of explicit errorMessageText is strongly encouraged.
//


/////////////////////////////////////////////////////////////////////////////////////////////////
// ERROR_AND_DIE
//
// Present in all builds.
// No condition; always triggers if reached.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Shuts down the app
//
// Use this when reaching a certain line of code should never happen under any circumstances,
// and continued execution is dangerous or impossible.
//
#define ERROR_AND_DIE( errorMessageText )												\
{																					\
	FatalError( __FILE__, __LINE__, errorMessageText );								\
}

#define ERROR_AND_DIE_GENERIC															\
{																					\
	FatalError( __FILE__, __LINE__, "Fatal unspecified error" );					\
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// GUARANTEE_OR_DIE
//
// Present in all builds.
// Triggers if condition is false.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Shuts down the app
//
#define GUARANTEE_OR_DIE( condition, errorMessageText )								\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		FatalError( __FILE__, __LINE__, errorMessageText, conditionText );			\
	}																				\
}

#define GUARANTEE_OR_DIE_GENERIC( condition )										\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		FatalError( __FILE__, __LINE__, "Fatal unmet guarantee", conditionText );			\
	}																				\
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// ASSERT_OR_DIE
//
// Removed if DISABLE_ASSERTS is enabled, typically in a Final build configuration.
// Triggers if condition is false.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Shuts down the app
//
#if defined( DISABLE_ASSERTS )
#define ASSERT_OR_DIE( condition, errorMessageText ) { (void)( condition ); }
#else
#define ASSERT_OR_DIE( condition, errorMessageText )								\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		FatalError( __FILE__, __LINE__, errorMessageText, conditionText );			\
	}																				\
}
#endif

#if defined( DISABLE_ASSERTS )
#define ASSERT_OR_DIE_GENERIC( condition ) { (void)( condition ); }
#else
#define ASSERT_OR_DIE_GENERIC( condition )										\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		FatalError( __FILE__, __LINE__, "Fatal unmet assertion", conditionText );	\
	}																				\
}
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////
// ERROR_RECOVERABLE
//
// Present in all builds.
// No condition; always triggers if reached.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Continues execution
//
#define ERROR_RECOVERABLE( errorMessageText )										\
{																					\
	RecoverableError( __FILE__, __LINE__, errorMessageText );						\
}

#define ERROR_RECOVERABLE_GENERIC													\
{																					\
	RecoverableError( __FILE__, __LINE__, "Unspecified error" );					\
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// GUARANTEE_RECOVERABLE
//
// Present in all builds.
// Triggers if condition is false.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Continues execution
//
#define GUARANTEE_RECOVERABLE( condition, errorMessageText )						\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		RecoverableError( __FILE__, __LINE__, errorMessageText, conditionText );	\
	}																				\
}

#define GUARANTEE_RECOVERABLE_GENERIC( condition )									\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		RecoverableError( __FILE__, __LINE__, "Unmet guarantee", conditionText );	\
	}																				\
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// ASSERT_RECOVERABLE
//
// Removed if DISABLE_ASSERTS is enabled, typically in a Final build configuration.
// Triggers if condition is false.
// Depending on the platform, this typically:
//	- Logs a warning to the console and/or log file
//	- Opens an error/message dialogue box
//	- Triggers a debug breakpoint (if appropriate development suite is present)
//	- Continues execution
//
#if defined( DISABLE_ASSERTS )
#define ASSERT_RECOVERABLE( condition, errorMessageText ) { (void)( condition ); }
#else
#define ASSERT_RECOVERABLE( condition, errorMessageText )						\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		RecoverableError( __FILE__, __LINE__, errorMessageText, conditionText );	\
	}																				\
}
#endif

#if defined( DISABLE_ASSERTS )
#define ASSERT_RECOVERABLE_GENERIC( condition ) { (void)( condition ); }
#else
#define ASSERT_RECOVERABLE_GENERIC( condition )									\
{																					\
	if( !(condition) )																\
	{																				\
		const char* conditionText = #condition;										\
		RecoverableError( __FILE__, __LINE__, "Unmet assertion", conditionText );	\
	}																				\
}
#endif



#endif // include_ErrorWarningAssert
