#pragma once

#include "GameFramework/Actor.h"
#include "WeatherDataStruct.h"
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
		bool bUseRealtimeWeatherData = false;

	// Current Weather Data
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		FWeatherDataStruct CurrentWeatherData;

	void GetWeatherData(/*location//bUseSystemTime//manualtime)*/);

};