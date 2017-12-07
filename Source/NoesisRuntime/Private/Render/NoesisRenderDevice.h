////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

class FNoesisRenderDevice : public Noesis::RenderDevice
{
	static const uint32 VertexBufferSize = 512 * 1024;
	static const uint32 IndexBufferSize = 128 * 1024;

	FVertexBufferRHIRef DynamicVertexBuffer;
	FIndexBufferRHIRef DynamicIndexBuffer;
	uint32 VertexBufferOffset;
	uint32 IndexBufferOffset;

	FNoesisRenderDevice();
	virtual ~FNoesisRenderDevice();

public:
	static const int32 NUM_SHADERS = 84;
	static uint32 RHICmdListTlsSlot;
	FVertexDeclarationRHIRef VertexDeclarations[NUM_SHADERS];
	uint16 VertexStrides[NUM_SHADERS];
	class FNoesisVSBase* VertexShaders[NUM_SHADERS];
	class FNoesisPSBase* PixelShaders[NUM_SHADERS];

	class FNoesisRenderTarget* CurrentRenderTarget;

	static FNoesisRenderDevice* Get();
	static void Destroy();

	static Noesis::Ptr<Noesis::Texture> CreateTexture(UTexture* Texture);

	static void ThreadLocal_SetRHICmdList(FRHICommandList* RHICmdList);
	static FRHICommandList* ThreadLocal_GetRHICmdList();

	// RenderDevice interface
	virtual const Noesis::DeviceCaps& GetCaps() const override;
	virtual Noesis::Ptr<Noesis::RenderTarget> CreateRenderTarget(const char* Label, uint32 Width, uint32 Height, uint32 SampleCount) override;
	virtual Noesis::Ptr<Noesis::RenderTarget> CloneRenderTarget(const char* Label, Noesis::RenderTarget* SharedRenderTarget) override;
	virtual Noesis::Ptr<Noesis::Texture> CreateTexture(const char* Label, uint32 Width, uint32 Height, uint32 NumLevels, Noesis::TextureFormat::Enum TextureFormat) override;
	virtual void UpdateTexture(Noesis::Texture* Texture, uint32 Level, uint32 X, uint32 Y, uint32 Width, uint32 Height, const void* Data) override;
	virtual void BeginRender(bool Offscreen) override;
	virtual void SetRenderTarget(Noesis::RenderTarget* Surface) override;
	virtual void BeginTile(const Noesis::Tile& Tile, uint32 SurfaceWidth, uint32 SurfaceHeight) override;
	virtual void EndTile() override;
	virtual void ResolveRenderTarget(Noesis::RenderTarget* Surface, const Noesis::Tile* Tiles, uint32 NumTiles) override;
	virtual void EndRender() override;
	virtual void* MapVertices(uint32 Bytes) override;
	virtual void UnmapVertices() override;
	virtual void* MapIndices(uint32 Bytes) override;
	virtual void UnmapIndices() override;
	virtual void DrawBatch(const Noesis::Batch& Batch) override;
	// End of RenderDevice interface
};
