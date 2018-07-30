#pragma once

#define CUBE_INDEX_SIZE 36
extern WORD g_aCubeIndex[];
#define CUBE_VERTEX_SIZE 8
extern D3DXVECTOR3 g_aCubeVertex[];

#define WINSTARTX 20						//윈도우 시작좌표X
#define WINSTARTY 20						//윈도우 시작좌표Y
//#define WINSIZEX 1600						//윈도우 가로크기
#define WINSIZEX 1300						//윈도우 가로크기
//#define WINSIZEY 960						//윈도우 세로크기
#define WINSIZEY 660						//윈도우 세로크기


#define SINGLETON(class_name) private:\
	class_name();\
	~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SAFE_WNDPROC(p) if(p) {(p)->WndProc(hWnd, message, wParam, lParam);}
#define SAFE_UPDATE(p) if(p) { (p)->Update();}
#define SAFE_RENDER(p) if(p) { (p)->Render();}
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) { if(p) { delete [] p; p = NULL; } }

#define SYNTHESIZE(varType, varName, funName) \
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_REF(varType, varName, funName) \
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var) { varName = var; }

#define SCREEN_POINT(lParam) LOWORD(lParam), HIWORD(lParam)

#define METHOD_WNDPROC(method) void method(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)


#define WHITE	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define BLACK	D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)
#define RED		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN	D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE	D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
#define YELLOW	D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)

enum FontType
{
	FontType_NORMAL,
	FontType_BULLETTOTAL
};

enum SCENE_INDEX {
	SCENE_LOADING,
	SCENE_LOBBY,
	SCENE_LOBBYLOADING,
	SCENE_OBJMAP
};

enum TAG_DISPLAYOBJECT {
	TAG_PLAYER,
	TAG_MAP,
	TAG_PARTICLE
};

enum class ITEM_LIST
{
	AK47,
	ARMOR,
	BACKPACK,
	HEAD,
	END
};

enum class ITEM_INTO
{
	FIELD,
	INVEN,
	EQUIPMENT,
	ITEMBOX,
	END
};

enum ePlayerState {
	//무기 들고 앉아있을때 애니메이션
	Rifle_crouch_walk_right_front,   //(걸으면서)오른쪽앞
	Rifle_crouch_walk_right,      //(걸으면서)오른쪽
	Rifle_crouch_walk_right_back,   //(걸으면서)오른쪽뒤
	Rifle_crouch_walk_back,      //(걸으면서)뒤로
	Rifle_crouch_walk_left_back,   //(걸으면서)왼쪽뒤
	Rifle_crouch_walk_left,      //(걸으면서)왼쪽
	Rifle_crouch_walk_left_front,   //(걸으면서)왼쪽앞
	Rifle_crouch_walk_front,      //(걸으면서)앞으로
	Rifle_crouch_run_right_front,   //(뛰면서)오른쪽앞
	Rifle_crouch_run_right,      //(뛰면서)오른쪽
	Rifle_crouch_run_right_back,   //(뛰면서)오른쪽뒤
	Rifle_crouch_run_back,         //(뛰면서)뒤로
	Rifle_crouch_run_left_back,   //(뛰면서)왼쪽뒤
	Rifle_crouch_run_left,         //(뛰면서)왼쪽
	Rifle_crouch_run_left_front,   //(뛰면서)왼쪽앞
	Rifle_crouch_run_front,      //(뛰면서)앞으로
	Rifle_crouch_fastrun,   //뛰기
	Rifle_crouch_pickup,   //템줍는 모션
	Rifle_crouch_idle,      //기본상태

	//무기 들고 서 있을때 애니메이션
	Rifle_stand_walk_right_front,//(걸으면서)오른쪽앞
	Rifle_stand_walk_right,      //(걸으면서)오른쪽
	Rifle_stand_walk_right_back,//(걸으면서)오른쪽뒤
	Rifle_stand_walk_back,      //(걸으면서)뒤로
	Rifle_stand_walk_left_back,   //(걸으면서)왼쪽뒤
	Rifle_stand_walk_left,      //(걸으면서)왼쪽
	Rifle_stand_walk_left_front,//(걸으면서)왼쪽앞
	Rifle_stand_walk_front,      //(걸으면서)앞으로
	Rifle_stand_run_right_front,//(뛰면서)오른쪽앞
	Rifle_stand_run_right,      //(뛰면서)오른쪽
	Rifle_stand_run_right_back,   //(뛰면서)오른쪽뒤
	Rifle_stand_run_back,      //(뛰면서)뒤로
	Rifle_stand_run_left_back,   //(뛰면서)왼쪽뒤
	Rifle_stand_run_left,      //(뛰면서)왼쪽
	Rifle_stand_run_left_front,   //(뛰면서)왼쪽앞
	Rifle_stand_run_front,      //(뛰면서)앞으로
	Rifle_stand_fastrun,   //뛰기
	Rifle_stand_jump,      //점프
	Rifle_stand_pickup,      //템줍는 모션
	Rifle_stand_idle,      //기본상태

   
    //무기 안들고 앉아있을때 애니메이션
    Melee_crouch_walk_right_front,   //(걸으면서)오른쪽앞
    Melee_crouch_walk_right,      //(걸으면서)오른쪽
    Melee_crouch_walk_right_back,   //(걸으면서)오른쪽뒤
    Melee_crouch_walk_back,         //(걸으면서)뒤로
    Melee_crouch_walk_left_back,   //(걸으면서)왼쪽뒤
    Melee_crouch_walk_left,         //(걸으면서)왼쪽
    Melee_crouch_walk_left_front,   //(걸으면서)왼쪽앞
    Melee_crouch_walk_front,      //(걸으면서)앞으로
    Melee_crouch_run_right_front,   //(뛰면서)오른쪽앞
    Melee_crouch_run_right,         //(뛰면서)오른쪽
    Melee_crouch_run_right_back,   //(뛰면서)오른쪽뒤
    Melee_crouch_run_back,         //(뛰면서)뒤로
    Melee_crouch_run_left_back,      //(뛰면서)왼쪽뒤
    Melee_crouch_run_left,         //(뛰면서)왼쪽
    Melee_crouch_run_left_front,   //(뛰면서)왼쪽앞
    Melee_crouch_run_front,         //(뛰면서)앞으로
    Melee_crouch_fastrun,      //뛰기
    Melee_crouch_punch1,      //주먹질3
    Melee_crouch_punch2,      //주먹질2
    Melee_crouch_punch3,      //주먹질1
    Melee_crouch_pickup,      //템줍는 모션
    Melee_crouch_idle,      //기본상태
   
   
    //무기 안들고 서 있을때 애니메이션
    Melee_stand_walk_right_front,//(걸으면서)오른쪽앞
    Melee_stand_walk_right,      //(걸으면서)오른쪽
    Melee_stand_walk_right_back,//(걸으면서)오른쪽뒤
    Melee_stand_walk_back,      //(걸으면서)뒤로
    Melee_stand_walk_left_back,   //(걸으면서)왼쪽뒤
    Melee_stand_walk_left,      //(걸으면서)왼쪽
    Melee_stand_walk_left_front,//(걸으면서)왼쪽앞
    Melee_stand_walk_front,      //(걸으면서)앞으로
    Melee_stand_run_right_front,//(뛰면서)오른쪽앞
    Melee_stand_run_right,      //(뛰면서)오른쪽
    Melee_stand_run_right_back,   //(뛰면서)오른쪽뒤
    Melee_stand_run_back,      //(뛰면서)뒤로
    Melee_stand_run_left_back,   //(뛰면서)왼쪽뒤
    Melee_stand_run_left,      //(뛰면서)왼쪽
    Melee_stand_run_left_front,   //(뛰면서)왼쪽앞
    Melee_stand_run_front,      //(뛰면서)앞으로
    Melee_stand_fastrun,      //뛰기
    Melee_stand_punch1,      //주먹질1
    Melee_stand_punch2,      //주먹질2
    Melee_stand_punch3,      //주먹질3
    Melee_stand_jump,      //점프
    Melee_stand_pickup,      //템줍는 모션
    Melee_stand_idle,      //기본상태

    ////Action.x파일
    Medkit,      //구급상자
    Bandage,   //붕대
    Drink,      //드링크
    PainKiller,   //진통제
    Aiming,      //정조준
    Rebound,   //반동
    Reload,      //장전
    Stand_idle,   //서있는 상태
    Crouch_idle,//앉아있는 상태
    Gun_acceptance,   //총 넣기
    Null,      //null이라는데 what?
    Swap_Weapon,//총 꺼내기
    Stand_Punch1,      //서서 펀치1
    Stand_Punch2,      //서서 펀치2
    Stand_Punch3,      //서서 펀치3
    Crouch_punch1,      //앉아서 펀치1
    Crouch_punch2,      //앉아서 펀치2
    Crouch_punch3,      //앉아서 펀치3
    Aiming2,         //정조준2
    Stand_Rifle_idle,   //서서 앉은 상태
    Crouch_rifle_idle,   //총들고 앉은 상태
    Kar98_reload,
    Kar98_boltAction,
    Falldown,   //쓰러지는 모션
    Faint_idle   //기절모션
};

enum eActionState {
	////Action.x파일
	//Medkit,      //구급상자
	//Bandage,   //붕대
	//Drink,      //드링크
	//PainKiller,   //진통제
	//Aiming,      //정조준
	//Rebound,   //반동
	//Reload,      //장전
	//Stand_idle,   //서있는 상태
	//Crouch_idle,//앉아있는 상태
	//Gun_acceptance,   //총 넣기
	//Null,      //null이라는데 what?
	//Swap_Weapon,//총 꺼내기
	//Stand_Punch1,      //서서 펀치1
	//Stand_Punch2,      //서서 펀치2
	//Stand_Punch3,      //서서 펀치3
	//Crouch_punch1,      //앉아서 펀치1
	//Crouch_punch2,      //앉아서 펀치2
	//Crouch_punch3,      //앉아서 펀치3
	//Aiming2,         //정조준2
	//Stand_Rifle_idle,   //서서 앉은 상태
	//Crouch_rifle_idle,   //총들고 앉은 상태
	//Kar98_reload,
	//Kar98_boltAction,
	//Falldown,   //쓰러지는 모션
	//Faint_idle   //기절모션
 };

struct KEYBOARD_STATE
{
	D3DXVECTOR3 deltaPos;
	D3DXVECTOR3 deltaRot;
	bool bJump;
	bool bSit;
	bool bWalk;
};

//	1. Position 정점의 좌표 x,y,z(float)				: D3DFVF_XYZ
// 	2. RHW (float)                                  : D3DFVF_XYZRHW (D3DFVF_XYZ 또는 D3DFVF_NORMAL과 같이 사용불가)
// 	3. Blending Weight Data 결합 가중치 (float)		: D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 	4. Vertex Normal 정점의 법선 벡터 x,y,z(float)	: D3DFVF_NORMAL
// 	5. Vertex Point Size 정점의 점 크기 (float)		: D3DFVF_PSIZE
// 	6. Diffuse Color (DWORD)						: D3DFVF_DIFFUSE
// 	7. Specular Color (DWORD)						: D3DFVF_SPECULAR
// 	8. Texture Coordinate Set 1 (float)             : D3DFVF_TEX0 - D3DFVF_TEX8

struct VERTEX_PC
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	VERTEX_PC() {}
	VERTEX_PC(D3DXVECTOR3 _p, D3DCOLOR _c) : p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};

struct VERTEX_PNC
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;
	D3DCOLOR	c;

	VERTEX_PNC() {}
	VERTEX_PNC(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DCOLOR _c) : p(_p), n(_n), c(_c) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE, };
};

struct VERTEX_PT
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	VERTEX_PT() {}
	VERTEX_PT(D3DXVECTOR3 _p, D3DXVECTOR2 _t) : p(_p), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};

struct VERTEX_PCT
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	D3DXVECTOR2 t;
	D3DXVECTOR2 t1;

	VERTEX_PCT() {}
	VERTEX_PCT(D3DXVECTOR3 _p, D3DCOLOR _c, D3DXVECTOR2 _t) : p(_p), c(_c), t(_t), t1(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2, };
};

struct VERTEX_RHWC
{
	VERTEX_RHWC() {}
	VERTEX_RHWC(D3DXVECTOR4 _p, D3DCOLOR _c) : p(_p), c(_c) {}

	D3DXVECTOR4 p;
	D3DCOLOR	c;

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE, };
};

struct VERTEX_PN
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;

	VERTEX_PN() {}
	VERTEX_PN(D3DXVECTOR3 _p, D3DXVECTOR3 _n) : p(_p), n(_n) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct VERTEX_PNT
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;

	VERTEX_PNT() {}
	VERTEX_PNT(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t) : p(_p), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};

struct VERTEX_BLENDING
{
	D3DXVECTOR3 p;
	float		weights[3];
	DWORD		index;
	//D3DXCOLOR	c;
	D3DXVECTOR2	t;

	VERTEX_BLENDING() {}
	VERTEX_BLENDING(D3DXVECTOR3 _p, float* _weights, DWORD _i, D3DXCOLOR _c, D3DXVECTOR2 _t)
		: p(_p), index(_i), t(_t) {
		weights[0] = _weights[0];
		weights[1] = _weights[1];
		weights[2] = _weights[2];
	}

	enum { FVF = D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_TEX1 };
};

struct MTLTEX : public BaseObject
{
	D3DMATERIAL9		material;
	LPDIRECT3DTEXTURE9	pTexture;
	int					id;

	MTLTEX() {
		ZeroMemory(&material, sizeof(D3DMATERIAL9));
		pTexture = NULL;
	}

	void SetMaterial(const D3DMATERIAL9 &_material)
	{
		material = _material;
	}
	D3DMATERIAL9 GetMaterial() { return material; }
	void SetTexture(LPDIRECT3DTEXTURE9 _pTexture)
	{
		pTexture = _pTexture;
	}
	LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
};

struct ASE_POS_SAMPLE
{
	int			tick;
	D3DXVECTOR3 position;
};

struct ASE_ROT_SAMPLE
{
	int				tick;
	D3DXQUATERNION	quaternion;
};

struct ASE_SCENE
{
	int numFirstFrame;
	int numLastFrame;
	int frameSpeed;
	int ticksPerFrame;
};

struct BoundingSphere
{
	D3DXVECTOR3 center;
	float      radius;
	bool      isPicked;

	BoundingSphere() :isPicked(false) {}
	BoundingSphere(D3DXVECTOR3 _center, float _radius) :center(_center),
		radius(_radius), isPicked(false) {}
};


DWORD FtoDw(float f);

float GetRandomFloat(float lowBound, float highBound);

LPD3DXFONT GetFont(FontType type);

bool CompareStr(const char * str1, const char * str2);

namespace DXUtil
{
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 8.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 8.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 8.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 8.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);

	void ComputeNormal(D3DXVECTOR3* out, D3DXVECTOR3* p0, D3DXVECTOR3* p1, D3DXVECTOR3* p2);

	D3DLIGHT9 InitDirectional(D3DXVECTOR3* dir, D3DXCOLOR* c);
	D3DLIGHT9 InitPoint(D3DXVECTOR3* pos, D3DXCOLOR* c);
	D3DLIGHT9 InitSpot(D3DXVECTOR3* dir, D3DXVECTOR3* pos, D3DXCOLOR* c);

	void InitVertexBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb, LPVOID vertices, DWORD fvf, UINT vtxCnt, UINT stride);
	void InitIndexBuffer(LPDIRECT3DINDEXBUFFER9 &pIb, LPVOID indices, UINT idxCnt, UINT stride);
}

