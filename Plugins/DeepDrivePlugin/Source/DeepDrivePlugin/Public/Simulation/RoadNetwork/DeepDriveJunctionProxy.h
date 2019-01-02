

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/Simulation/RoadNetwork/DeepDriveRoadNetwork.h"
#include "DeepDriveJunctionProxy.generated.h"

class ADeepDriveRoadSegmentProxy;
class ADeepDriveRoadLinkProxy;

USTRUCT(BlueprintType)
struct FDeepDriveLaneConnectionProxy
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	ADeepDriveRoadSegmentProxy	*FromSegment = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	ADeepDriveRoadSegmentProxy	*ToSegment = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	ADeepDriveRoadSegmentProxy	*ConnectionSegment = 0;
};


UCLASS()
class DEEPDRIVEPLUGIN_API ADeepDriveJunctionProxy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeepDriveJunctionProxy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const TArray<ADeepDriveRoadLinkProxy*>& getLinksIn();

	const TArray<ADeepDriveRoadLinkProxy*>& getLinksOut();

	const TArray<FDeepDriveLaneConnectionProxy>& getLaneConnections();

protected:

	UPROPERTY(EditAnywhere, Category = Configuration)
	TArray<ADeepDriveRoadLinkProxy*>	LinksIn;

	UPROPERTY(EditAnywhere, Category = Configuration)
	TArray<ADeepDriveRoadLinkProxy*>	LinksOut;

	UPROPERTY(EditAnywhere, Category = Configuration)
	TArray<FDeepDriveLaneConnectionProxy>	LaneConnections;

};

inline const TArray<ADeepDriveRoadLinkProxy*>& ADeepDriveJunctionProxy::getLinksIn()
{
	return LinksIn;
}

inline const TArray<ADeepDriveRoadLinkProxy*>& ADeepDriveJunctionProxy::getLinksOut()
{
	return LinksOut;
}

inline const TArray<FDeepDriveLaneConnectionProxy>& ADeepDriveJunctionProxy::getLaneConnections()
{
	return LaneConnections;
}
