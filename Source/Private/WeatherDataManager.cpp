#include "WeatherDataManager.h"
#include "Kismet/KismetMathLibrary.h"


AWeatherDataManager::AWeatherDataManager(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeatherDataManager::OnConstruction(const FTransform& Transform)
{

}

void AWeatherDataManager::BeginPlay()
{
	Super::BeginPlay();
}

void AWeatherDataManager::Tick(float DeltaWeatherData)
{
	Super::Tick(DeltaWeatherData);
}