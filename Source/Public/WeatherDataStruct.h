#pragma once

#include "CoreMinimal.h"
#include "WeatherDataStruct.generated.h"


USTRUCT(BlueprintType)
struct FWeatherDataStruct
{
	GENERATED_USTRUCT_BODY()

	// Normalized global wind direction.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherData")
		FVector WindDirection;

	// Wind Speed in kmh, (Multiply by 27.7778f to convert to games cm/s.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherData")
		float WindSpeed;

	// Normalized global Sun Direction. If Z is less than 0, then the sun is below horizion.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherData")
		FVector SunDirection;

	// Air humidity as a percentage, from 0 - 100%.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherData")
		int32 Humidity;

	// Air Temperature in celsius at Sealevel.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherData")
		int32 SeaLevelTemperature;

	// Rate of Precipitation (rain/snow fall rate) in 0-100. Probably need a manual override control for it.  //Sascha: Pretty sure we can use this for hail rate as well.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherData")
		float PrecipitationRate;

	// Air pressure hpa, Placeholder in case we need it.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherData")
		float AirPressure;


	// Fully initialized constructor
	FWeatherDataStruct(FVector InWindDirection = FVector(0, 1, 0), float InWindSpeed = 13, FVector InSunDirection = FVector(.8,.8,.8), int32 InHumidity = 35,
		int32 InSeaLevelTemperature = -1, float InPrecipitationRate = 32, float InAirPressure = 32)
	{
		WindDirection = InWindDirection;
		WindSpeed = InWindSpeed;
		SunDirection = InSunDirection;
		Humidity = InHumidity;
		SeaLevelTemperature = InSeaLevelTemperature;
		PrecipitationRate = InPrecipitationRate;
		AirPressure = InAirPressure;
	}
};
