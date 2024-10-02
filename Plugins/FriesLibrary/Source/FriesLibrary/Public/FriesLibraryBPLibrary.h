// Copyright Frytinhas UE Market 2024. All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FriesLibraryTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FriesLibraryBPLibrary.generated.h"

/*
Welcome to Fries Library, here you can find some functions that can help in the development of your project. 
This plugin was originally designed for Unreal Engine 5.1.1, although over time I will update with new functions 
or for new versions of Unreal Engine.
*/

// Forward declarations
class UOverallScalability;

UCLASS()
class UFriesLibraryBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// Development Functions (Ex: Print with different variables)

/*
 *  Prints a string to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
 *  And most importantly, it tells you where it's called
 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintStringWithTell(const UObject* WorldContextObject, const FString InString = TEXT("Hello"), const bool bPrintToScreen = true,
		const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.5, 0.0, 1.0), const float Duration = 2.f, const FName Key = NAME_None);

/*
 *  Prints a boolean to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintBoolean(const UObject* WorldContextObject, const bool bInBoolean = true, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
		const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(1.0, 0.0, 0.0), const FName Key = NAME_None);

/*
 *  Prints a byte to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
    static void PrintByte(const UObject* WorldContextObject, const uint8 Byte, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
    	const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.0, 0.1, 0.075), const FName Key = NAME_None);

/*
 *  Prints a byte to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintClass(const UObject* WorldContextObject, const TSubclassOf<UObject> Class, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
		const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.1, 0.0f, 0.3f), const FName Key = NAME_None);
	
/*
 *  Prints a color code to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "4", DevelopmentOnly), Category = "FriesLibrary|Development")
    static void PrintColor(const UObject* WorldContextObject, const FColor Color, const float Duration = 2.f, const bool bTextColorEqualColor = true,
    	const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true,
    	const FLinearColor TextColor = FLinearColor(0.0, 0.0, 1.0), const FName Key = NAME_None);

/*
 *  Prints a linear color code to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "4", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintLinearColor(const UObject* WorldContextObject, const FLinearColor LinearColor, const float Duration = 2.0f, const bool bTextColorEqualColor = true,
		const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true,
		const FLinearColor TextColor = FLinearColor(0.0, 0.0, 1.0), const FName Key = NAME_None);

/*
 *  Prints a linear color code from slate color to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	/* Removed because UE 5.4 errors
	 *UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "4", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintSlateColor(const UObject* WorldContextObject, const FSlateColor SlateColor, const float Duration = 2.0f, const bool bTextColorEqualColor = true,
		const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, const bool bPrintToLog = true,
		const FLinearColor TextColor = FLinearColor(0.0, 0.0, 1.0), const FName Key = NAME_None);*/

/*
 *  Prints a integer 64 to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintInteger64(const UObject* WorldContextObject, const int64 IntegerValue = 0, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
		const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.0, 1.0, 0.5), const FName Key = NAME_None);

/*
 *  Prints a integer to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintInteger(const UObject* WorldContextObject, const int32 IntegerValue = 0, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
		const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.4, 1.0, 0.3), const FName Key = NAME_None);

/*
 *  Prints a float to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintFloat(const UObject* WorldContextObject, const float FloatValue = 0.f, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
		const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.0, 1.0, 0.0), const FName Key = NAME_None);

/*
 *  Prints a name to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintName(const UObject* WorldContextObject, const FName InName = NAME_None, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
		const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.5, 0.0, 1.0), const FName Key = NAME_None);

/*
 *  Prints a vector to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintVector(const UObject* WorldContextObject, const FVector VectorValue = FVector(0.f, 0.f, 0.f), const float Duration = 2.f,
		const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(1.0, 1.0, 0.0),
		const FName Key = NAME_None);

/*
 *  Prints a rotator to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintRotator(const UObject* WorldContextObject, const FRotator RotatorValue = FRotator(0.f, 0.f, 0.f), const float Duration = 2.f,
		const bool bPrintFunctionOwner = true, const bool bPrintToScreen = true, bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(0.25, 0.25, 1.0),
		const FName Key = NAME_None);

/*
 *  Prints a transform to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintTransform(const UObject* WorldContextObject, const FTransform& TransformValue, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
		const bool bPrintToScreen = true, const bool bPrintToLog = true, const FLinearColor TextColor = FLinearColor(1.0, 0.25, 0.0), const FName Key = NAME_None);

/*
 *  Prints a object to the log, and optionally, to the screen
 *  If Print To Log is true, it will be visible in the Output Log window.
*/
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "log print", AdvancedDisplay = "3", DevelopmentOnly), Category = "FriesLibrary|Development")
	static void PrintObject(const UObject* WorldContextObject, const UObject* Object, const float Duration = 2.f, const bool bPrintFunctionOwner = true,
		const bool bPrintToScreen = true, const bool bPrintToLog = true, const bool bPrintIfInvalid = true,const FLinearColor TextColor = FLinearColor(0.0, 0.25, 1.0),
		const FName Key = NAME_None);

// Simplified language
	// Get current language as a enumeration
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Internationalization")
	static EFlLanguages GetLanguage();

// Simplified language
	// Set a new language by enumeration
	UFUNCTION(BlueprintCallable, Category = "FriesLibrary|Internationalization")
	static void SetLanguage(const EFlLanguages NewLanguage);
	
// Additional Functions to Game User Settings
	// Get current ambient occlusion method
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "get ambient"), Category = "FriesLibrary|Settings|Ambient Occlusion")
	static EFlAmbientOcclusion GetAmbientOcclusion();

// Additional Functions to Game User Settings
	// Get current anti-aliasing method
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "get anti"), Category = "FriesLibrary|Settings|Anti-Aliasing")
	static EFlAntiAliasingMethod GetAntiAliasingMethod();

// Additional Functions to Game User Settings
	// Get current global illumination method
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "get global"), Category = "FriesLibrary|Settings|Illumination")
	static EFlGlobalIlluminationMethod GetGlobalIllumination();

// Additional Functions to Game User Settings
	// Get current CPU name
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "cpu"), Category = "FriesLibrary|Settings|Info")
	static FString GetCurrentCPUName()
	{
		return FWindowsPlatformMisc::GetCPUBrand();
	}

// Additional Functions to Game User Settings
	// Get current CPU chipset name
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "chip"), Category = "FriesLibrary|Settings|Info")
	static FString GetChipset()
	{
		return FWindowsPlatformMisc::GetCPUChipset();
	}

// Additional Functions to Game User Settings
	// Get current user epic ID
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "id"), Category = "FriesLibrary|Settings|Info")
	static FString GetEpicID()
	{
		return FWindowsPlatformMisc::GetEpicAccountId();
	}

// Additional Functions to Game User Settings
	// Get machine mac address
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "mac"), Category = "FriesLibrary|Settings|Info")
	static TArray<uint8> GetMacAddress()
	{
		return FWindowsPlatformMisc::GetMacAddress();
	}
	
// Additional Functions to Game User Settings
    // Get current OS version (Ex: 10.0.22631.1.1.256.64bit)
    UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "os"), Category = "FriesLibrary|Settings|Info")
    static FString GetOSVersion()
	{
		return FWindowsPlatformMisc::GetOSVersion();
	}

// Additional Functions to Game User Settings
	// Get current GPU name
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "gpu"), Category = "FriesLibrary|Settings|Info")
	static FString GetCurrentGPUName()
	{
		return FWindowsPlatformMisc::GetPrimaryGPUBrand();
	}
	
// Additional Functions to Game User Settings
	// Set ambient occlusion method
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "set ambient"), Category = "FriesLibrary|Settings|Ambient Occlusion")
	static void SetAmbientOcclusion(const UObject* WorldContextObject, const EFlAmbientOcclusion NewAmbientOcclusion, const bool bSaveInConfig = true);

// Additional Functions to Game User Settings
	// Set anti-aliasing method
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "set anti"), Category = "FriesLibrary|Settings|Anti-Aliasing")
	static void SetAntiAliasingMethod(const UObject* WorldContextObject, const EFlAntiAliasingMethod NewAntiAliasingMethod, const bool bSaveInConfig = true);

// Additional Functions to Game User Settings
	// Set global illumination method
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "set global"), Category = "FriesLibrary|Settings|Illumination")
	static void SetGlobalIlluminationMethod(const UObject* WorldContextObject, const EFlGlobalIlluminationMethod NewGlobalIllumination, const bool bSaveInConfig = true);
	
// Additional Functions to Game User Settings
	// Save and apply all game user settings
	UFUNCTION(BlueprintCallable, Category = "FriesLibrary|Settings")
	static void SaveGameUserSettings();

// Additional Functions to Game User Settings
	// Get scalability level by scalability type
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "scalability"), Category = "FriesLibrary|Settings|Scalability")
    static EFlEngineScalabilityLevel GetScalabilityLevel(const EFlEngineScalabilityType ScalabilityToGet);

// Additional Functions to Game User Settings
	// Modify scalability by level
	UFUNCTION(BlueprintCallable, meta = (Keywords = "scalability"), Category = "FriesLibrary|Settings|Scalability")
    static void ModifyScalability(const EFlEngineScalabilityType ScalabilityToModify, const EFlEngineScalabilityLevel NewScalabilityLevel, const bool bSaveInConfig = true);

// Additional Functions to Game User Settings
	// Modify all scalability types by level
	UFUNCTION(BlueprintCallable, meta = (Keywords = "scalability"), Category = "FriesLibrary|Settings|Scalability")
    static void SetOverallScalability(const UOverallScalability* OverallData, const EFlEngineScalabilityLevel NewScalabilityLevel);
	
/// RHI Functions
	// Set current RHI in the game (Needs restart)
	UFUNCTION(BlueprintCallable, Category = "FriesLibrary|Settings|RHI")
	static void SetGraphicsRHI(const EGraphicsRHI GraphicsRHI);
// RHI Functions
	// Get current RHI in the game (Needs restart)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Settings|RHI")
	static EGraphicsRHI GetCurrentGraphicsRHI();

// Ray Tracing Additional Functions
	// Verify if ray tracing is available in current GPU.
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "raytracing"), Category = "FriesLibrary|Settings|Ray Tracing")
	static bool RayTracingIsSupported();

// Ray Tracing Additional Functions
	// Verify is ray tracing is enabled.
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "raytracing"), Category = "FriesLibrary|Settings|Ray Tracing")
	static bool RayTracingIsEnabled();

// Ray Tracing Additional Functions
	// Set ray tracing enabled/disabled in current GPU if available.
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "raytracing"), Category = "FriesLibrary|Settings|Ray Tracing")
	static bool SetRayTracing(const UObject* WorldContextObject, const bool bEnabled);

// Random Things that can help you
	// Get a random code (contains numbers and letters), useful to create hard code
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Code", meta = (AdvancedDisplay = "2"))
	static FString RandomCode(const int Length, const bool bToUpper, const bool bRandomCase, const int Min = 0, const int Max = 9);
	
// Random Things that can help you
	// Get a random code (only letters)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Code", meta = (AdvancedDisplay = "2"))
	static FString RandomCodeAlphabetic(const int Length, const bool bToUpper, const bool bRandomCase);

// Random Things that can help you
	// Get a random code (only numbers), Ex: useful to create a door code
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Code")
	static FString RandomCodeNum(const int Length, const bool bContainsZero);

// Random Things that can help you
	// Get a random color
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Color")
	static FColor RandomColor(const bool bConstOpacity, const uint8 OpacityIfConst = 255);

// Random Things that can help you
	// Get a random linear color
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Color")
	static FLinearColor RandomLinearColor(const bool bConstOpacity, const float OpacityIfConst = 1.0f);

// Random Things that can help you
	// Get a random byte
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Math")
	static uint8 RandomByte();

// Random Things that can help you
	// Get a random byte by range
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Math")
	static uint8 RandomByteInRange(const uint8 Min = 0, const uint8 Max = 255);
	
// Random Things that can help you
	// Get a random letter, is useful for generating random text, as a plate
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Math")
	static FString RandomLetter(const bool bToUpper = true);
	
// Random Things that can help you
	// Get a random letter by range, is useful for generating random text, as a plate
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FriesLibrary|Utilities|Random|Math")
	static FString RandomLetterInRange(int32 Min = 0, int32 Max = 26, const bool bToUpper = true);

// Random Things that can help you
	// Trace to center of the player camera, if CameraComponent is null, the method get camera from the player pawn
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", CallableWithoutWorldContext, Keywords = "camera", AdvancedDisplay = "3"), Category = "FriesLibrary|Utilities")
	static bool LineTraceToCenterOfCamera(const UObject* WorldContextObject, class UCameraComponent* CameraComponent,FHitResult& HitResult, const float TraceDistance, 
	ETraceTypeQuery CollisionChannel, EDrawDebugTrace::Type DebugType, const TArray<AActor*>& ActorsToIgnore);
	
// Random Things that can help you
    // Get the player controller from actor referenced
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DefaultToSelf = "Actor", Keywords = "get"), Category = "FriesLibrary|Utilities")
	static APlayerController* GetPlayerControllerFromActor(AActor* Actor);
	
// Random Things that can help you
    // Create an array with all materials of mesh in own dynamic version
    UFUNCTION(BlueprintCallable, meta = (Keywords = "dynamic"), Category = "FriesLibrary|Utilities")
    static TArray<UMaterialInstanceDynamic*> CreateDynamicInstanceMaterialArray(UPrimitiveComponent* Mesh, const FName OptionalName = "None");

// Random Things that can help you
	// Takes every client to a new level
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "travel", AdvancedDisplay = "2"), Category = "FriesLibrary|Utilities")
	static void ServerTravel(const UObject* WorldContextObject, const FString LevelName = "", const bool bSeamlessTravel = true);
};
