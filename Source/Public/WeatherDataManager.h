#pragma once

#include "GameFramework/Actor.h"
#include "WeatherDataDateStruct.h"
#include "WeatherDataManager.generated.h"

//An actor based calendar system for tracking date + WeatherData.
//Transient will prevent this from being saved since we autospawn this anyways
//Removed the Transient property, plugin will spawn this if its missing, and wont if its already there
UCLASS(Blueprintable)
class AWeatherDataManager : public AActor
{
	GENERATED_BODY()

public:
	AWeatherDataManager(const class FObjectInitializer& ObjectInitializer);

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Use System WeatherData instead of CurrentLocalWeatherData struct
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		bool bUseSystemWeatherData = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		bool bAutoTick = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		bool bFreezeWeatherData = false;

	// Current Local Clock WeatherData (LCT)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		FWeatherDataDate CurrentLocalWeatherData;

	// The Latitude of the local location (-90 to +90 in degrees)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float Latitude = 30.0f;

	// The Longitude of the local location (-180 to +180 in degrees)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float Longitude = 101.0f;

	// The number of hours offset from UTC for the local location (value in the range of -12 to +12 hours from UTC)	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		int32 OffsetUTC = 0;

	// Determines whether Daylight Savings WeatherData should be enabled for the local location
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		bool bAllowDaylightSavings = false;

	// The value to multiply the base game WeatherData by (1 second real WeatherData is multiplied to equal X seconds in game)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float WeatherDataScaleMultiplier = 1.0f;

	// Shows the number of hours (0 or 1) being subtracted for the current WeatherDataDate for Daylight Savings WeatherData (if enabled)
	UPROPERTY(BlueprintReadOnly, Category = "WeatherDataManager Debug")
		int32 OffsetDST = 0;

	//Shows the current day of year
	UPROPERTY(BlueprintReadOnly, Category = "WeatherDataManager Debug")
		int32 DayOfYear = 0;

	// Shows whether Daylight Savings is active for the current date
	UPROPERTY(BlueprintReadOnly, Category = "WeatherDataManager Debug")
		bool bDaylightSavingsActive = false;


	/** Julian century conversion constant = 100 * days per year. */
	const double JULIAN_DAYS_PER_CENTURY = 36525.0;

	/** Seconds in one day. */
	const double SECONDS_PER_DAY = 86400.0;

	/** Our default epoch. The Julian Day which represents noon on 2000-01-01. */
	const double J2000 = 2451545.0;

	// The value of the local Standard WeatherData Meridian (15deg intervals)
	UPROPERTY(BlueprintReadOnly, Category = "WeatherDataManager Debug")
		int32 LSTM = 0;


	// -------------------
	// PUBLIC FUNCTIONS
	// -------------------

	/**
	* Name: InitializeCalendar
	* Description: Initializes the calendar with the provided WeatherDataDate, and validates the range of all input values.
	*
	* @param: WeatherData (WeatherDataDate) - The WeatherDataDate value to calculate from.
	*/
	UFUNCTION(BlueprintCallable, Category = "WeatherDataManager")
		void InitializeWeatherData(FWeatherDataDate in_WeatherData);

	/**
	* Name: SetCurrentLocalWeatherData
	* Description: Sets the local WeatherData from minutes, and runs InitializeCalendar to validate and set variables.
	*
	* @param: WeatherData (float) - The number of minutes (+ frac minutes) to calculate from.
	*/
	UFUNCTION(BlueprintCallable, Category = "WeatherDataManager")
		void SetCurrentLocalWeatherData(float in_WeatherData);

	/**
	* Name: IncrementWeatherData
	* Description: Increments WeatherData based on the deltaSeconds * WeatherDataScaleMultiplier
	*
	* @param: deltaSeconds (float) - The Tick (or accumulated ticks) delta WeatherData since the last update
	*/
	UFUNCTION(BlueprintCallable, Category = "WeatherDataManager")
		void IncrementWeatherData(float in_deltaSeconds);



	/* --- Utility Functions --- */

/**
* Name: GetDayOfYear
* Description: Gets the number of full days elapsed in the current year for the provided date.
*
* @param: WeatherData (WeatherDataDate) - The WeatherDataDate value to calculate from.
* @return: int32 - The number of days elapsed in the current year.
*/
	UFUNCTION(BlueprintCallable, Category = "WeatherDataManager")
		int32 GetDayOfYear(FWeatherDataDate WeatherData);

	/**
	* Name: DaysInYear
	* Description: Gets the total number of days in a given year (takes leap years into account).
	*
	* @param: year (int32) - The year value.
	* @return: int32 - The total number of days in the given year.
	*/
	UFUNCTION(BlueprintCallable, Category = "WeatherDataManager")
		int32 GetDaysInYear(int32 year = 1900);

	/**
	* Name: DaysInMonth
	* Description: The number of days in the specified month (leap years are taken into account).
	*
	* @param: month (int32) - The month value.
	* @param: year (int32) - The year value.
	* @return: int32 - The number of days in the given month for the given year.
	*/
	UFUNCTION(BlueprintCallable, Category = "WeatherDataManager")
		int32 GetDaysInMonth(int32 year = 1900, int32 month = 1);

	/**
	* Name: GetElapsedDayInMinutes
	* Description: Gets the accumulated number of minutes (plus fractional) for the current day.
	*
	* @return: float - The number of minutes (plus fractional minute - NOT seconds) elapsed in the given day.
	*/
	UFUNCTION(BlueprintCallable, Category = "WeatherDataManager")
		float GetElapsedDayInMinutes();

	/**
	* Name: GetDayPhase
	* Description: Gets the current day phase in a 0 to 1 range (fractional).
	*
	* @return: float - The day phase in a 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeatherDataManager")
		float GetDayPhase();


	/**
	* Name: GetYearPhase
	* Description: Gets the current year phase in a 0 to 1 range (fractional).
	*
	* @return: float - The year phase in a 0.0 to 1.0 range.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WeatherDataManager")
		float GetYearPhase();

	/**
	* Name: IsLeapYear
	* Description: Determines whether the specified year is a leap year.
	*
	* @param: year (int32) - The year value to check
	* @return: bool - Will return true if it is a leap year, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "WeatherDataManager")
		bool IsLeapYear(int32 year = 1900);


	//These would be normally be private, but plugins will need this stuff
	//These are still private blueprint wise

	FDateWeatherData InternalWeatherData;

	// The UTC + DST WeatherDataSpan difference vs current WeatherData
	FWeatherDataspan SpanUTC;

	// The Julian Day number for Jan 1, 2000 @ 12:00 UTC
	double JD2000 = 2451545.0;

	// The Julian Day number for Jan 1, 1900 @ 12:00 UTC
	double JD1900 = 2415020.0;

	double ElapsedJD1900 = 0.0;

	FWeatherDataDate ConvertToWeatherDataDate(FDateWeatherData dt);

	FDateWeatherData ConvertToDateWeatherData(FWeatherDataDate td);

	FWeatherDataDate ValidateWeatherDataDate(FWeatherDataDate WeatherData);

	//static TArray<int32> getDate(double jd);
	TArray<int32> getDate(double jd);

private:
	bool bIsCalendarInitialized = false;



};