// Fill out your copyright notice in the Description page of Project Settings.


#include "BPVCBPLib.h"

#include "EdGraphSchema_K2.h"
#include "JsonObjectWrapper.h"

void UBPVCBPLib::IterateBlueprints()
{
	// Get the Asset Registry module 
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<
		FAssetRegistryModule>("AssetRegistry");

	// Asset Class filter
	TArray<FName> ClassFilter;
	ClassFilter.Add(UBlueprint::StaticClass()->GetFName());

	// Query for all assets in the Asset Registry.
	TArray<FAssetData> AssetList;
	AssetRegistryModule.Get().GetAssetsByClass(UBlueprint::StaticClass()->GetFName(), AssetList, true);

	for (auto AssetData : AssetList)
	{
		// Now you can access each blueprint properties and stuff, for example the asset's path
		FString AssetPath = AssetData.GetSoftObjectPath().ToString();
		UBlueprint* Blueprint = LoadAndCastBlueprint(AssetPath);
		IterateNodesInBlueprints(Blueprint);
	}
}

UBlueprint* UBPVCBPLib::LoadAndCastBlueprint(FString AssetPath)
{
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UBlueprint::StaticClass(), false, true);

	// Load the asset - this will return an UObject

	// Validate that the asset does exist
	if (UObject* LoadedAsset = StaticLoadObject(UBlueprint::StaticClass(), nullptr, *AssetPath))
	{
		// Cast the UObject to a UBlueprint

		if (UBlueprint* LoadedBlueprint = Cast<UBlueprint>(LoadedAsset))
		{
			return LoadedBlueprint;
		}
	}

	// In case of failure
	return nullptr;
}


void UBPVCBPLib::IterateNodesInBlueprints(UBlueprint* Blueprint)
{
	// Get the Generated class from the Blueprint
	UBlueprintGeneratedClass* BGClass = Cast<UBlueprintGeneratedClass>(Blueprint->GeneratedClass);
	// 创建一个jsonobj用于存储蓝图的节点信息
	TSharedPtr<FJsonObject> BlueprintJsonObj = MakeShared<FJsonObject>();
	// Iterate over each graph within the Blueprint
	for (UEdGraph* Graph : Blueprint->UbergraphPages)
	{
		TSharedPtr<FJsonObject> GraphJsonObj = MakeShared<FJsonObject>();
		// Check if it's the EventGraph
		if (!Graph->GetSchema()->GetClass()->IsChildOf<UEdGraphSchema_K2>())
		{
			continue;;
		}
		for (auto Node : Graph->Nodes)
		{
			// Do stuff with the node..
			FString NodeName = Node->GetName();
			TArray<TSharedPtr<FJsonValue>> OtherNodes;
			UE_LOG(LogTemp, Log, TEXT("%s"), *NodeName);
			for (auto Pin : Node->Pins)
			{
				if (Pin->LinkedTo.IsEmpty())
				{
					continue;
				}
				for (auto Link : Pin->LinkedTo)
				{
					auto OwningNode = Link->GetOwningNode();
					OtherNodes.Add(MakeShareable(
						new FJsonValueString(OwningNode->GetName() + "" + Node->GetNodeTitle(ENodeTitleType::MenuTitle).ToString())));
				}
			}
			GraphJsonObj->SetArrayField(Node->GetName() + " " + Node->GetNodeTitle(ENodeTitleType::MenuTitle).ToString(), OtherNodes);
		}
		BlueprintJsonObj->SetObjectField(Graph->GetName(), GraphJsonObj);
	}
	TSharedPtr<FJsonObject> JsonObject = BlueprintJsonObj;
	FString JsonString;
	// TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonString, 2);
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString, 0);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer, true);
	FFileHelper::SaveStringToFile(
		JsonString, *(FPaths::ProjectContentDir() + "BPVC/" + Blueprint->GetName() + ".json"));
}

void UBPVCBPLib::SaveAllBlueprints()
{
	TFuture<void> Future = Async(EAsyncExecution::Thread, IterateBlueprints);
}
