#pragma once

#include "CoreMinimal.h"
#include "WeatherDataDateStruct.generated.h"


USTRUCT(BlueprintType)
struct FWeatherDataDate
{
	GENERATED_USTRUCT_BODY()

	// Placeholder data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherData")
	int32 Placeholder;



	// Fully initialized constructor
	FWeatherDataDate(int32 InPlaceholder = 0)
	{
		Placeholder = InPlaceholder;

	}
};
