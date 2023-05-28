// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectLibrarySubsystem.h"

void UObjectLibrarySubsystem::LoadObjectLibrary(const FString& Path, TArray<UObject*>& Assets)
{
	const TSubclassOf<UDataAsset> Subclass;
	if(ObjectLibrary == nullptr)
		ObjectLibrary = UObjectLibrary::CreateLibrary(Subclass, false, GIsEditor);
	if (ObjectLibrary == nullptr) return;

	//ObjectLibrary->AddToRoot();
	const FString NewPath = TEXT("/Game") / Path;
	ObjectLibrary->LoadAssetDataFromPath(NewPath);
	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);

	for (int32 i = 0; i < AssetDatas.Num(); ++i)
	{
		FAssetData& AssetData = AssetDatas[i];

		UObject* Asset = AssetData.GetAsset();
		if (Asset)
		{
			Assets.Add(AssetData.GetAsset());
		}
	}
	Assets.Sort();
}
