// For copyright see LICENSE in EnvironmentProject root dir, or:
//https://github.com/UE4-OceanProject/OceanProject/blob/Master-Environment-Project/LICENSE

#include "WeatherDataPlugin.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY(WeatherDataPlugin);

void FWeatherDataPlugin::StartupModule()
{
	UE_LOG(WeatherDataPlugin, Log, TEXT("WeatherDataPlugin StartupModle() Register OnWorldCreated delegate"));

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//Auto create our WeatherDataManager
	//This is called everyWeatherData UWorld is created, which is a lot in the editor (every opened BP gets a UWorld)
	FWorldDelegates::OnPostWorldInitialization.AddRaw(this, &FWeatherDataPlugin::InitSingletonActor);
}

void FWeatherDataPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
}

void FWeatherDataPlugin::EnforceSingletonActor(UWorld* World)
{
	//Make sure there is only one instance of this actor!
	//Actor is not blueprintable, but users will find other ways!!
	bool bFoundFirstInstance = false;
	for (TActorIterator<AWeatherDataManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		if (bFoundFirstInstance == false)
		{
			bFoundFirstInstance = true;
		}
		else
		{
			ActorItr->Destroy();
		}
	}
}

AWeatherDataManager * FWeatherDataPlugin::SpawnSingletonActor(UWorld* World)
{
	FVector location = FVector(0, 0, 0);
	FRotator rotate = FRotator(0, 0, 0);
	FActorSpawnParameters SpawnInfo;
	return World->SpawnActor<AWeatherDataManager>(AWeatherDataManager::StaticClass(), location, rotate, SpawnInfo);
}

void FWeatherDataPlugin::InitSingletonActor(UWorld* World, const UWorld::InitializationValues IVS)
{
	//Make sure we are in the correct UWorld!
	if (World->WorldType == EWorldType::Game || EWorldType::PIE || EWorldType::GamePreview || EWorldType::GameRPC || EWorldType::Editor)
	{
		//If we already have a WeatherDataManagerEditorActor in the editor level, do not spawn another one
		//This also auto spawns a WeatherDataManagerActor in the game world, if the user somehow sneaks a map in
		//that has not been opened while the plugin was active!

		EnforceSingletonActor(World);

		for (TActorIterator<AWeatherDataManager> ActorItr(World); ActorItr; ++ActorItr)
		{
			//If WeatherDataManager already exists
			return;
		}

		//Spawn WeatherDataManager since there isn't one already
		SpawnSingletonActor(World);
	}
}

AWeatherDataManager * FWeatherDataPlugin::GetSingletonActor(UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();

	EnforceSingletonActor(World);

	for (TActorIterator<AWeatherDataManager> ActorItr(World); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}

	//In the impossible case that we don't have an actor, spawn one!
	return SpawnSingletonActor(World);
}

IMPLEMENT_MODULE(FWeatherDataPlugin, WeatherDataPlugin)

