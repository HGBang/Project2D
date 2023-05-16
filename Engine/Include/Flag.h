#pragma once

enum AXIS2D
{
	AXIS2D_X,
	AXIS2D_Y,
	AXIS2D_MAX
};

enum AXIS
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX
};

enum class MeshType : unsigned char
{
	Sprite,
	UI,
	Static,
	Animation
};

enum class BufferType : unsigned char
{
	Vertex,
	Index
};

enum class ShaderType : unsigned char
{
	Graphic,
	Compute
};

enum class ComponentType : unsigned char
{
	Scene,
	Object
};

enum class SceneComponentType : unsigned char
{
	Sprite
};

enum class EShaderBufferType : unsigned char
{
	Vertex = 0x1,
	Pixel = 0x2,
	Domain = 0x4,
	Hull = 0x8,
	Geometry = 0x10,
	Compute = 0x20,
	Graphic = Vertex | Pixel | Domain | Hull | Geometry,
	All = Vertex | Pixel | Domain | Hull | Geometry | Compute
};

enum class ECameraType : unsigned char
{
	Camera2D,
	Camera3D,
	CameraUI
};

enum class EImageType : unsigned char
{
	Atlas,
	Frame,
	Array
};

enum class ESamplerType : unsigned char
{
	Point,
	Linear,
	Anisotropic
};

enum class ERenderStateType : unsigned char
{
	Blend,
	Rasterizer,
	DepthStencil,
	End
};

enum class EAnimation2DType : int
{
	None = -1,
	Atlas,
	Frame,
	Array
};

enum class ECollision_Channel
{
	Default,
	Mouse,
	Player,
	Monster,
	Die,
	Custom3,
	Custom4,
	Custom5,
	Custom6,
	Custom7,
	Custom8,
	Custom9,
	Max
};

enum class ECollision_Interaction
{
	Ignore,
	Collision
};

enum class ECollider_Type
{
	Collider2D,
	Collider3D
};

enum class ECollider2D_Type
{
	Box2D,
	OBB2D,
	Sphere2D,
	Pixel
};

enum class ECollider3D_Type
{
	Box,
	OBB,
	Sphere
};

enum class ECollision_Result
{
	Collision,
	Release,
	Click,
	Max
};


enum class EPixelCollision_Type
{
	None,
	Color_Ignore,
	Color_Confirm,
	Alpha_Ignore,
	Alpha_Confirm
};

enum class ESceneComponentType
{
	Scene,
	Primitive,
	Sprite,
	Camera,
	Box2D,
	OBB2D,
	Sphere2D,
	Pixel,
	Collider,
	Collider2D,
	Collider3D,
	TargetArm,		
	TileMap,
	Max
};

enum class ETileShape
{
	Rect,
	Isometric
};

enum class ETileOption
{
	None,
	Wall,
	End
};

enum class EProgressBarTextureType
{
	Back,
	Bar,
	Max
};

enum class EProgressBarDir
{
	RightToLeft,
	LeftToRight,
	TopToBottom,
	BottomToTop
};