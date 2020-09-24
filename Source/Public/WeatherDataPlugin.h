// For copyright see LICENSE in EnvironmentProject root dir, or:
//https://github.com/UE4-OceanProject/OceanProject/blob/Master-Environment-Project/LICENSE

#pragma once

#include "Engine/World.h"
#include "WeatherDataManager.h"

DECLARE_LOG_CATEGORY_EXTERN(WeatherDataPlugin, Log, All);

class WEATHERDATAPLUGIN_API FWeatherDataPlugin : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void EnforceSingletonActor(UWorld* World);
	AWeatherDataManager * SpawnSingletonActor(UWorld* World);
	void InitSingletonActor(UWorld* World, const UWorld::InitializationValues IVS);

	AWeatherDataManager * GetSingletonActor(UObject* WorldContextObject);

	/**
	* Singleton-like access to this module's interface.  This is just for convenience!
	* Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	*
	* @return Returns singleton instance, loading the module on demand if needed
	*/
	static inline FWeatherDataPlugin& Get()
	{
		return FModuleManager::LoadModuleChecked< FWeatherDataPlugin >("WeatherDataPlugin");
	}

	/**
	* Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	*
	* @return True if the module is loaded and ready to use
	*/
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("WeatherDataPlugin");
	}
};

