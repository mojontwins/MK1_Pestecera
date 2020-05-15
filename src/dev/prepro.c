# 1 "mk1.c"

# 4 "c:\z88dk10\include/cpcrslib.h"
extern void __FASTCALL__ cpc_PutSp (void);
extern void __FASTCALL__ __LIB__ cpc_ShowTileMap(int x);
extern void __FASTCALL__ __LIB__ cpc_ShowScrTileMap(int x);
extern void __FASTCALL__ __LIB__ cpc_ShowScrTileMap2(int x);
extern void __FASTCALL__ __LIB__ cpc_UpdScrAddresses(unsigned int x);
extern void __LIB__ cpc_TouchTileXY(unsigned char x, unsigned char y);
extern void __LIB__ cpc_TouchTileSpXY(unsigned char x, unsigned char y);
extern void __CALLEE__ __LIB__ cpc_ResetTouchedTiles(void);
extern void __CALLEE__ __LIB__ cpc_UpdScr(void);
extern void __CALLEE__ __LIB__ cpc_ShowTouchedTiles2(void);
extern void __CALLEE__ __LIB__ cpc_ShowTouchedTiles(void);
extern void __FASTCALL__ __LIB__ cpc_PutSpTileMap(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutSpTileMap4x8(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutSpTileMap8x16(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutSpTileMap8x24(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutSpTileMapO(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutMaskSpTileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutTrSpTileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutORSpTileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutSpTileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutCpSpTileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutMaskSpriteTileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutTrSpriteTileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutTrSp4x8TileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutTrSp8x16TileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_PutTrSp8x24TileMap2b(int sprite);
extern void __FASTCALL__ __LIB__ cpc_SuperbufferAddress(int sprite);
extern void __FASTCALL__ __LIB__ cpc_UpdateTileMap(int spritelist);
extern void __LIB__ cpc_SpUpdX(int sprite, char x);
extern void __LIB__ cpc_SpUpdY(int sprite, char y);
extern unsigned char __LIB__ cpc_CollSp(int sprite1, int sprite2);
extern void __LIB__ cpc_SetTile(unsigned char x, unsigned char y, unsigned char byte);
extern void __LIB__ cpc_SetTouchTileXY(unsigned char x, unsigned char y, unsigned char byte);
extern unsigned char __LIB__ cpc_ReadTile(unsigned char x, unsigned char y);
extern void __LIB__ cpc_PutSp(int *sprite, char *alto, char *ancho, int *posicion);
extern void __LIB__ cpc_PutSpXOR(int *sprite, char *alto, char *ancho, int *posicion);
extern void __CALLEE__ __LIB__ cpc_PutSpriteXOR(int *sprite, int *posicion);
extern void __CALLEE__ __LIB__ cpc_PutMaskSprite(int *sprite, int *posicion);
extern void __CALLEE__ __LIB__ cpc_PutSprite(int *sprite, int *posicion);
extern void __LIB__ cpc_PutMaskSp(int *sprite, char *alto, char *ancho, int *posicion);
extern void __LIB__ cpc_PutSpTr(int *sprite, char *alto, char *ancho, int *posicion);
extern void __LIB__ cpc_PutMaskSp2x8(int *sprite, int *posicion);
extern void __LIB__ cpc_PutMaskSp4x16(int *sprite, int *posicion);
extern void __LIB__ cpc_PutTile2x8(int *tile, char *x, char *y);
extern void __LIB__ cpc_PutTile4x16(int *tile, char *x, char *y);
extern void __FASTCALL__ __LIB__ cpc_SpRLM1(int sprite);
extern void __FASTCALL__ __LIB__ cpc_SpRRM1(int sprite);
extern void __LIB__ cpc_SetInk(unsigned char pos, unsigned char color);
extern void __LIB__ cpc_SetColour(unsigned char pos, unsigned char color);
extern void __FASTCALL__ __LIB__ cpc_SetBorder(unsigned char color);
extern void __FASTCALL__ __LIB__ cpc_SetMode(unsigned char color);
extern void __FASTCALL__ __LIB__ cpc_SetModo(unsigned char x);
extern char __FASTCALL__ __LIB__ cpc_TestKey(unsigned char tecla);
extern char __CALLEE__ __LIB__ cpc_AnyKeyPressed(void);
extern void __FASTCALL__ __LIB__ cpc_RedefineKey(unsigned char tecla);
extern void __LIB__ cpc_AssignKey(unsigned char tecla, int valor);
extern void __CALLEE__ __LIB__ cpc_DeleteKeys(void);
extern void __FASTCALL__ __LIB__ cpc_PrintStr(int *cadena);
extern int __LIB__ cpc_GetScrAddress(char *x, char *y);
extern void __CALLEE__ __LIB__ cpc_Uncrunch(int *origen, int *destino);
extern void __CALLEE__ __LIB__ cpc_UnExo(int *origen, int *destino);
extern void __LIB__ cpc_GetSp(int *sprite, char *alto, char *ancho, int *posicion);
extern void __LIB__ cpc_PrintGphStr(int *cadena, int *destino);
extern void __LIB__ cpc_PrintGphStr2X(int *cadena, int *destino);
extern void __LIB__ cpc_PrintGphStrXY(int *cadena, char *x, char *y);
extern void __LIB__ cpc_PrintGphStrXY2X(int *cadena, char *x, char *y);
extern void __LIB__ cpc_PrintGphStrM1(int *cadena, int *destino);
extern void __LIB__ cpc_PrintGphStrXYM1(int *cadena, char *x, char *y);
extern void __LIB__ cpc_PrintGphStrM12X(int *cadena, int *destino);
extern void __LIB__ cpc_PrintGphStrXYM12X(int *cadena, char *x, char *y);
extern void __LIB__ cpc_PrintGphStrStd(int *cadena, int *destino);
extern void __LIB__ cpc_PrintGphStrStdXY(int *cadena, char *x, char *y);
extern void __LIB__ cpc_SetInkGphStr(char *color, char *valor);
extern void __LIB__ cpc_SetInkGphStrM1(char *color, char *valor);
extern void __FASTCALL__ __LIB__ cpc_InitTileMap(int tiles);
extern char __CALLEE__ __LIB__ cpc_ScrollLeft0(void);
extern char __CALLEE__ __LIB__ cpc_ScrollRight0(void);
extern void __LIB__ cpc_GetTiles(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int buffer);
extern void __LIB__ cpc_PutTiles(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int buffer);
extern void __LIB__ cpc_TouchTiles(unsigned char x, unsigned char y, unsigned char w, unsigned char h);
extern void __LIB__ cpc_RRI(unsigned int pos, unsigned char w, unsigned char h);
extern void __LIB__ cpc_RLI(unsigned int pos, unsigned char w, unsigned char h);
extern void __CALLEE__ __LIB__ cpc_DisableFirmware(void);
extern void __CALLEE__ __LIB__ cpc_EnableFirmware(void);
extern void __CALLEE__ __LIB__ cpc_ClrScr(void);
extern void __CALLEE__ __LIB__ cpc_ScanKeyboard(void);
extern char __FASTCALL__ __LIB__ cpc_TestKeyF(unsigned char tecla);
# 3 "c:\z88dk10\include/cpcwyzlib.h"
extern void __FASTCALL__ __LIB__ cpc_WyzLoadSong(unsigned char numero);
extern void __LIB__ cpc_WyzStartEffect(unsigned char canal, unsigned char efecto);
extern void __CALLEE__ __LIB__ cpc_WyzSetPlayerOn(void);
extern void __CALLEE__ __LIB__ cpc_WyzSetPlayerOff(void);
extern void __FASTCALL__ __LIB__ cpc_WyzConfigurePlayer(char valor);
extern char __CALLEE__ __LIB__ cpc_WyzTestPlayer(void);
extern void __LIB__ cpc_WyzInitPlayer(int sonidos, int pautas, int efectos, int canciones);
extern void __FASTCALL__ __LIB__ cpc_WyzSetTempo(unsigned char tempo);
#asm
# 11 "mk1.c"
XREF _nametable
LIB cpc_UpdTileTable
LIB cpc_InvalidateRect
#endasm
# 330 "my/config.h"
unsigned char behs [] = {
0, 8, 8, 0, 0, 8, 8, 1, 8, 8, 8, 8, 8, 8,10,10,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
# 7 "prototypes.h"
void break_wall (void);


void bullets_init (void);
void bullets_update (void);
void bullets_fire (void);
void bullets_move (void);


void enems_init (void);
void enems_draw_current (void);
void enems_load (void);
void enems_kill (void);
void enems_move (void);


unsigned char collide (void);
unsigned char cm_two_points (void);
unsigned char rand (void);
unsigned int abs (signed int n);
void step (void);
void cortina (void);


void hotspots_init (void);
void hotspots_do (void);


void player_init (void);
void player_calc_bounding_box (void);
unsigned char player_move (void);
void player_deplete (void);
void player_kill (unsigned char sound);


void simple_coco_init (void);
void simple_coco_shoot (void);
void simple_coco_update (void);




void SetRAMBank(void);


void get_resource (unsigned char n, unsigned int destination);
void unpack (unsigned int address, unsigned int destination);


void beep_fx (unsigned char n);


void prepare_level (void);
void game_ending (void);
void game_over (void);
void time_over (void);
void pause_screen (void);
signed int addsign (signed int n, signed int value);
void espera_activa (int espera);
void locks_init (void);
char player_hidden (void);
void run_fire_script (void);
void process_tile (void);
void draw_scr_background (void);
void draw_scr (void);
void select_joyfunc (void);
unsigned char mons_col_sc_x (void);
unsigned char mons_col_sc_y (void);
unsigned char distance (void);
int limit (int val, int min, int max);


void blackout (void);


unsigned char attr (unsigned char x, unsigned char y);
unsigned char qtile (unsigned char x, unsigned char y);
void draw_coloured_tile (void);
void invalidate_tile (void);
void invalidate_viewport (void);
void draw_invalidate_coloured_tile_g (void);
void draw_coloured_tile_gamearea (void);
void draw_decorations (void);
void update_tile (void);
void print_number2 (void);
void draw_objs ();
void print_str (void);
void blackout_area (void);
void clear_sprites (void);


void mem_save (void);
void mem_load (void);
void tape_save (void);
void tape_load (void);
void sg_submenu (void);


void add_tilanim (unsigned char x, unsigned char y, unsigned char t);
void do_tilanims (void);
#asm
# 5 "definitions.h"
.vpClipStruct defb 2, 2 + 20, 1, 1 + 30
.fsClipStruct defb 0, 24, 0, 32
#endasm


unsigned char pad0;
# 21
unsigned char safe_byte @ 0xC7FF;
# 36
typedef struct sprite {
unsigned int sp0;
unsigned int sp1;
unsigned int coord0;
signed char cox, coy;
unsigned char cx, cy;
unsigned char ox, oy;
void *invfunc;
void *updfunc;
} SPR;

SPR sp_sw [1 + 3 + 0 + 3] @ 0xE000 + 0x600;
unsigned char *spr_next [1 + 3 + 0 + 3] @ 0xE000 + 0x600 + (1 + 3 + 0 + 3)*16;
unsigned char spr_on [1 + 3 + 0 + 3] @ 0xE000 + 0x600 + (1 + 3 + 0 + 3)*18;
unsigned char spr_x [1 + 3 + 0 + 3] @ 0xE000 + 0x600 + (1 + 3 + 0 + 3)*19;
unsigned char spr_y [1 + 3 + 0 + 3] @ 0xE000 + 0x600 + (1 + 3 + 0 + 3)*20;

unsigned char enoffs;



char asm_number;
unsigned int asm_int;
unsigned int asm_int_2;
unsigned int seed;
unsigned char half_life;
# 98
signed int p_x, p_y;
signed int p_vx, p_vy;
unsigned char p_saltando, p_cont_salto;
unsigned char p_frame, p_subframe, p_facing;
unsigned char p_estado;
unsigned char p_ct_estado;
unsigned char p_gotten, pregotten;
unsigned char p_life, p_objs, p_keys;
unsigned char p_fuel;
unsigned char p_killed;
unsigned char p_disparando;
unsigned char p_facing_v, p_facing_h;
unsigned char p_ammo;
unsigned char p_killme;
unsigned char p_kill_amt;
unsigned char p_tx, p_ty;
# 117
signed int ptgmx, ptgmy;

const unsigned char *spacer = "            ";

unsigned char enit, enspit;


unsigned char en_an_base_frame [3] @ 0xD000 + 0x600;
unsigned char en_an_frame [3] @ 0xD000 + 0x600 + 3;
unsigned char en_an_count [3] @ 0xD000 + 0x600 + 3 * 2;
unsigned char en_an_sprid [3] @ 0xD000 + 0x600 + 3 * 3;
unsigned char en_an_state [3] @ 0xD000 + 0x600 + 3 * 4;
signed int en_an_x [3] @ 0xD000 + 0x600 + 3 * 5;
signed int en_an_y [3] @ 0xD000 + 0x600 + 3 * 7;
signed int en_an_vx [3] @ 0xD000 + 0x600 + 3 * 9;
signed int en_an_vy [3] @ 0xD000 + 0x600 + 3 * 11;
unsigned char en_an_alive [3] @ 0xD000 + 0x600 + 3 * 13;
unsigned char en_an_dead_row [3] @ 0xD000 + 0x600 + 3 * 14;
unsigned char en_an_rawv [3] @ 0xD000 + 0x600 + 3 * 15;
unsigned char cocos_x [3] @ 0xD000 + 0x600 + 3 * 16;
unsigned char cocos_y [3] @ 0xD000 + 0x600 + 3 * 17;
signed char cocos_mx [3] @ 0xD000 + 0x600 + 3 * 18;
signed char cocos_my [3] @ 0xD000 + 0x600 + 3 * 19;
unsigned char *en_an_next_frame [3] @ 0xD000 + 0x600 + 3 * 20;
# 160
unsigned char _en_x, _en_y;
unsigned char _en_x1, _en_y1, _en_x2, _en_y2;
signed char _en_mx, _en_my;
signed char _en_t;
signed char _en_life;

unsigned char *_baddies_pointer;
# 175
unsigned char map_attr [150] @ 0xC000 + 0x600;
unsigned char map_buff [150] @ 0xC000 + 0x600 + 150;
# 184
unsigned char hotspot_x;
unsigned char hotspot_y;
unsigned char hotspot_destroy;
unsigned char orig_tile;
# 193
unsigned char flags[32];


unsigned char o_pant;
unsigned char n_pant;
unsigned char is_rendering;
unsigned char level, slevel;

unsigned char warp_to_level = 0;

unsigned char maincounter;
# 225
unsigned char gpx, gpox, gpy, gpd, gpc, gpt;
unsigned char gpxx, gpyy, gpcx, gpcy;
unsigned char possee, hit_v, hit_h, hit, wall_h, wall_v;
unsigned char gpen_x, gpen_y, gpen_cx, gpen_cy, gpaux;
unsigned char tocado, active;
unsigned char gpit, gpjt;
unsigned char enoffsmasi;
unsigned char *map_pointer;
# 236
unsigned char rdx, rdy, rda, rdb, rdc, rdd, rdn, rdt;
# 244
int itj;
unsigned char objs_old, keys_old, life_old, killed_old;
# 263
unsigned char *gen_pt;
unsigned char playing;

unsigned char success;
# 271
unsigned char _x, _y, _n, _t;
unsigned char cx1, cy1, cx2, cy2, at1, at2;
unsigned char x0, y0, x1, y1;
unsigned char ptx1, pty1, ptx2, pty2;
unsigned char *_gp_gen;
# 291
const signed char _dx [] = { 0, 8, 0, -8 };
const signed char _dy [] = { -8, 0, 8, 0 };
# 4 "aplib.h"
unsigned int ram_address;
unsigned int ram_destination;
#asm
# 13
; aPPack decompressor
; original source by dwedit
; very slightly adapted by utopian
; optimized by Metalbrain

;hl = source
;de = dest

.depack ld ixl,128
.apbranch1 ldi
.aploop0 ld ixh,1 ;LWM = 0
.aploop call ap_getbit
jr nc,apbranch1
call ap_getbit
jr nc,apbranch2
ld b,0
call ap_getbit
jr nc,apbranch3
ld c,16 ;get an offset
.apget4bits call ap_getbit
rl c
jr nc,apget4bits
jr nz,apbranch4
ld a,b
.apwritebyte ld (de),a ;write a 0
inc de
jr aploop0
.apbranch4 and a
ex de,hl ;write a previous byte (1-15 away from dest)
sbc hl,bc
ld a,(hl)
add hl,bc
ex de,hl
jr apwritebyte
.apbranch3 ld c,(hl) ;use 7 bit offset, length = 2 or 3
inc hl
rr c
ret z ;if a zero is encountered here, it is EOF
ld a,2
adc a,b
push hl
ld iyh,b
ld iyl,c
ld h,d
ld l,e
sbc hl,bc
ld c,a
jr ap_finishup2
.apbranch2 call ap_getgamma ;use a gamma code * 256 for offset, another gamma code for length
dec c
ld a,c
sub ixh
jr z,ap_r0_gamma ;if gamma code is 2, use old r0 offset,
dec a
;do I even need this code?
;bc=bc*256+(hl), lazy 16bit way
ld b,a
ld c,(hl)
inc hl
ld iyh,b
ld iyl,c

push bc

call ap_getgamma

ex (sp),hl ;bc = len, hl=offs
push de
ex de,hl

ld a,4
cp d
jr nc,apskip2
inc bc
or a
.apskip2 ld hl,127
sbc hl,de
jr c,apskip3
inc bc
inc bc
.apskip3 pop hl ;bc = len, de = offs, hl=junk
push hl
or a
.ap_finishup sbc hl,de
pop de ;hl=dest-offs, bc=len, de = dest
.ap_finishup2 ldir
pop hl
ld ixh,b
jr aploop

.ap_r0_gamma call ap_getgamma ;and a new gamma code for length
push hl
push de
ex de,hl

ld d,iyh
ld e,iyl
jr ap_finishup


.ap_getbit ld a,ixl
add a,a
ld ixl,a
ret nz
ld a,(hl)
inc hl
rla
ld ixl,a
ret

.ap_getgamma ld bc,1
.ap_getgammaloop call ap_getbit
rl c
rl b
call ap_getbit
jr c,ap_getgammaloop
ret
#endasm
#asm
#endasm
#asm
#endasm
# 9 "pantallas.h"
extern unsigned char s_title [];
extern unsigned char s_marco [];
extern unsigned char s_ending [];
#asm


._s_title
BINARY "../bin/titlec.bin"
._s_marco
#endasm
#asm



BINARY "../bin/marcoc.bin"
#endasm
#asm



._s_ending
BINARY "../bin/endingc.bin"
#endasm



void blackout (void) {
# 47
}
# 5 "assets/pal.h"
const unsigned char my_inks [] = {
0x1C,
0x14,
0x12,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B,
0x0B
};
# 5 "assets/mapa.h"
unsigned char mapa [] = {
18, 16, 0, 0, 0, 0, 0, 1, 16, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 85, 85, 81, 0, 0, 0, 0, 85, 85, 85, 16, 0, 0, 0, 85, 85, 85, 82, 0, 0, 224, 21, 85, 85, 85, 16, 0, 0, 226, 17, 17, 17, 17, 208, 0, 0, 16, 0, 0, 0, 25, 208, 0, 1, 3, 51, 51, 49, 153, 208, 0, 21, 85, 85, 85,
0, 192, 0, 0, 0, 0, 0, 11, 203, 176, 0, 0, 0, 0, 0, 85, 85, 85, 0, 0, 0, 0, 5, 85, 0, 0, 0, 0, 0, 64, 85, 80, 85, 85, 0, 0, 6, 101, 85, 5, 85, 81, 0, 0, 0, 17, 16, 18, 17, 16, 4, 0, 0, 0, 0, 0, 1, 0, 96, 0, 51, 51, 51, 51, 36, 0, 0, 5, 85, 85, 85, 81, 96, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 96, 0, 0, 0, 0, 6, 96, 0, 0, 0, 96, 0, 64, 0, 0, 4, 0, 96, 0, 6, 96, 0, 0, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 102, 0, 0, 0, 0, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 96,
0, 0, 0, 192, 0, 176, 0, 0, 0, 0, 203, 192, 188, 0, 0, 0, 0, 85, 85, 85, 91, 0, 0, 0, 85, 85, 85, 85, 80, 0, 0, 85, 85, 85, 85, 85, 80, 0, 85, 85, 85, 85, 85, 85, 80, 1, 18, 17, 17, 17, 17, 33, 0, 0, 0, 1, 0, 0, 0, 0, 3, 49, 17, 32, 51, 51, 51, 0, 49, 16, 0, 3, 51, 51, 32,
0, 51, 51, 51, 51, 0, 0, 0, 3, 51, 51, 51, 48, 0, 0, 0, 51, 49, 3, 51, 0, 0, 0, 3, 51, 0, 51, 48, 0, 0, 0, 51, 51, 51, 51, 0, 0, 80, 1, 3, 51, 51, 36, 0, 5, 0, 39, 119, 119, 113, 96, 0, 16, 1, 17, 33, 17, 16, 0, 65, 0, 0, 0, 0, 0, 0, 6, 16, 0, 0, 0, 0, 0, 0, 1,
0, 0, 0, 12, 0, 0, 0, 0, 0, 85, 85, 85, 85, 80, 0, 0, 85, 85, 85, 85, 85, 80, 0, 85, 85, 85, 85, 85, 85, 80, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 17, 17, 17, 17, 17, 17, 17, 17, 0, 0, 1, 0, 0, 0, 1, 16, 0, 0, 240, 0, 0, 0, 17, 17, 17, 17, 17, 0, 0, 2,

26, 153, 0, 1, 17, 17, 17, 17, 9, 157, 0, 0, 0, 0, 0, 32, 154, 157, 0, 0, 0, 0, 1, 10, 9, 157, 16, 0, 0, 17, 32, 0, 154, 145, 0, 0, 0, 1, 0, 10, 9, 32, 0, 0, 0, 16, 0, 0, 145, 0, 0, 0, 1, 0, 0, 9, 16, 1, 0, 17, 16, 0, 0, 161, 0, 0, 0, 1, 0, 0, 0, 16, 0, 0, 0,
17, 17, 17, 17, 30, 0, 0, 0, 0, 0, 51, 50, 0, 4, 0, 0, 0, 3, 51, 16, 4, 96, 1, 0, 16, 51, 49, 0, 96, 0, 0, 0, 3, 60, 16, 0, 0, 0, 0, 0, 51, 17, 224, 0, 0, 0, 2, 19, 48, 16, 0, 0, 2, 0, 0, 51, 49, 0, 64, 0, 0, 0, 3, 51, 16, 6, 96, 0, 0, 0, 51, 49, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 102, 0, 0, 0, 102, 0, 0, 0, 0, 4, 0, 0, 0, 64, 0, 0, 0, 102, 0, 0, 6, 0, 0, 0, 0, 12, 12, 0, 0, 0, 6, 96, 0, 176, 176, 0, 0, 0, 0, 0, 13, 13, 0, 0, 0, 0, 0, 0, 160, 160, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 16, 3, 51, 51, 51, 49, 0, 32, 3, 51, 51, 51, 49, 16, 1, 3, 51, 51, 16, 51, 1, 0, 16, 51, 51, 48, 3, 51, 32, 1, 3, 16, 51, 51, 51, 48, 0, 16, 48, 3, 51, 51, 51, 48, 1, 192, 51, 51, 16, 51, 51, 112, 21, 80, 51, 48, 3, 51, 17, 2, 18, 3, 51, 51, 16, 50, 0, 16, 0, 51, 51, 48, 3, 16,
0, 0, 0, 0, 0, 0, 0, 16, 4, 132, 68, 132, 68, 132, 65, 4, 221, 221, 221, 221, 221, 221, 16, 217, 153, 153, 153, 153, 153, 145, 10, 17, 17, 17, 17, 17, 17, 16, 1, 0, 0, 0, 0, 0, 0, 119, 16, 51, 51, 0, 3, 51, 49, 17, 3, 51, 48, 0, 51, 51, 0, 16, 51, 51, 0, 3, 51, 16, 1, 3, 51, 48, 0, 51, 48,
17, 17, 17, 17, 16, 0, 0, 17, 0, 0, 0, 0, 16, 0, 1, 16, 51, 51, 0, 0, 0, 0, 33, 192, 51, 48, 0, 0, 0, 1, 17, 16, 51, 0, 0, 0, 12, 16, 0, 3, 48, 0, 0, 12, 177, 51, 51, 51, 0, 0, 49, 17, 19, 51, 51, 48, 0, 3, 0, 2, 16, 51, 51, 0, 0, 51, 51, 16, 3, 51, 48, 0, 3, 51, 49,

32, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 33, 0, 0, 0, 16, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 23, 119, 32, 0, 16, 0, 0, 1, 17, 17, 0, 2, 0, 0, 0, 16, 0, 0, 49, 16, 0, 0, 2, 3, 51, 51, 2, 0, 0, 0, 16, 51, 51, 51, 16, 0, 0, 1, 3, 51, 51, 49, 0, 0, 0, 16, 51, 18, 17,
0, 0, 3, 51, 16, 0, 0, 0, 0, 0, 51, 49, 224, 0, 0, 0, 0, 3, 51, 32, 96, 0, 0, 0, 16, 51, 49, 0, 0, 0, 0, 0, 3, 59, 16, 0, 0, 2, 3, 51, 49, 17, 0, 224, 0, 0, 51, 51, 0, 16, 0, 0, 3, 51, 51, 51, 50, 0, 0, 0, 50, 119, 119, 119, 22, 0, 0, 1, 17, 18, 17, 17, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 215, 0, 0, 0, 0, 0, 0, 9, 215, 7, 0, 0, 0, 112, 0, 170, 215, 212, 112, 0, 125, 0, 0, 9, 217, 221, 0, 13, 160, 0, 0, 169, 170, 157, 13, 144, 0, 0, 0, 160, 10, 160, 170, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 3, 51, 51, 51, 51, 49, 0, 32, 51, 51, 51, 51, 51, 16, 1, 3, 51, 51, 51, 51, 50, 0, 18, 3, 51, 51, 51, 51, 16, 1, 0, 51, 51, 51, 51, 49, 0, 16, 51, 51, 51, 51, 51, 16, 1, 3, 51, 51, 51, 51, 49, 0, 16, 51, 51, 51, 51, 51, 16, 1, 119, 119, 119, 119, 16, 49, 0, 17, 33, 17, 33, 17, 3, 32,
0, 16, 51, 51, 0, 3, 51, 48, 1, 16, 51, 48, 0, 51, 51, 0, 27, 3, 51, 0, 3, 51, 48, 1, 17, 3, 48, 0, 51, 17, 0, 16, 0, 51, 0, 3, 48, 0, 1, 3, 51, 48, 0, 51, 51, 0, 16, 51, 51, 0, 3, 51, 48, 1, 3, 51, 48, 0, 51, 51, 0, 23, 119, 119, 119, 183, 119, 112, 1, 18, 17, 17, 17, 17, 17,
51, 51, 51, 0, 0, 51, 51, 35, 51, 51, 48, 0, 3, 51, 49, 51, 51, 51, 0, 0, 51, 60, 17, 16, 51, 48, 0, 3, 51, 17, 0, 3, 51, 0, 0, 51, 48, 19, 51, 51, 48, 0, 3, 51, 49, 51, 51, 51, 3, 51, 49, 3, 35, 51, 51, 48, 51, 51, 0, 49, 119, 119, 119, 119, 16, 51, 51, 17, 17, 18, 17, 17, 16, 51, 49,

16, 0, 0, 1, 3, 49, 18, 17, 0, 0, 1, 16, 51, 0, 0, 32, 0, 0, 3, 51, 224, 51, 49, 0, 0, 0, 51, 48, 3, 51, 17, 0, 1, 17, 3, 51, 51, 49, 0, 0, 0, 30, 3, 51, 51, 16, 0, 0, 1, 0, 51, 62, 1, 7, 119, 0, 16, 51, 51, 0, 16, 85, 80, 1, 119, 117, 85, 82, 0, 0, 0, 17, 17, 17, 17,
17, 17, 17, 18, 16, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 51, 51, 51, 51, 16, 14, 0, 3, 48, 0, 0, 49, 0, 0, 0, 51, 0, 0, 3, 16, 0, 0, 3, 48, 14, 0, 50, 224, 0, 0, 51, 0, 0, 3, 16, 96, 0, 3, 48, 0, 0, 49, 0, 0, 0, 85, 0, 0, 5, 16, 0, 0, 1, 17, 0, 1, 17, 0, 6, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 12, 0, 6, 192, 0, 0, 0, 4, 96, 0, 6, 64, 0, 0, 4, 96, 0, 0, 6, 76, 68, 180, 96, 0, 0, 0, 6, 102, 102, 96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 17, 18, 17, 17, 16, 49, 0, 32, 0, 0, 0, 0, 3, 16, 1, 3, 51, 51, 51, 51, 49, 0, 16, 51, 51, 51, 51, 51, 32, 2, 17, 33, 3, 17, 33, 17, 0, 16, 0, 0, 48, 0, 0, 32, 1, 3, 51, 51, 51, 51, 49, 0, 16, 51, 51, 51, 51, 51, 16, 2, 17, 17, 18, 17, 3, 49, 0, 16, 0, 0, 0, 0, 51, 16,
0, 17, 17, 18, 17, 18, 17, 16, 1, 17, 17, 17, 17, 17, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 48, 0, 0, 0, 0, 0, 0, 51, 0, 48, 0, 0, 0, 0, 3, 48, 1, 0, 0, 0, 0, 0, 51, 0, 0, 0, 12, 0, 0, 3, 48, 3, 0, 11, 187, 203, 123, 199, 119, 112, 1, 17, 17, 17, 17, 17, 17,
17, 17, 17, 18, 17, 3, 51, 17, 33, 17, 17, 17, 16, 51, 17, 0, 0, 0, 0, 0, 3, 48, 32, 0, 0, 0, 0, 0, 0, 1, 51, 0, 51, 48, 51, 51, 48, 18, 0, 3, 51, 0, 0, 0, 2, 0, 0, 51, 48, 0, 0, 0, 19, 48, 3, 51, 3, 51, 51, 49, 119, 119, 188, 0, 51, 51, 51, 17, 17, 17, 17, 17, 3, 51, 49,

32, 0, 0, 1, 17, 17, 17, 18, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0, 1, 188, 51, 51, 49, 0, 0, 0, 17, 17, 17, 3, 16, 0, 0, 0, 0, 0, 0, 50, 0, 0, 0, 51, 51, 51, 51, 16, 0, 0, 1, 3, 51, 51, 49, 0, 0, 4, 28, 56, 8, 3, 36, 132, 132, 221, 221, 221, 221, 209, 221, 221, 218, 169, 153, 170, 169,
17, 16, 0, 17, 16, 0, 224, 0, 0, 0, 224, 1, 0, 0, 0, 0, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 1, 0, 0, 96, 0, 0, 16, 0, 16, 0, 224, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 1, 22, 0, 4, 128, 1, 188, 0, 1, 0, 4, 221, 221, 221, 221, 12, 20, 68, 217, 154, 169, 153, 157, 221, 221, 217, 153,
0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 72, 68, 132, 0, 0, 0, 0, 77, 221, 221, 212, 0, 0, 0, 77, 153, 153, 153, 212, 0, 0, 77, 153, 153, 153, 153, 212, 132, 45, 153, 153, 154, 170, 153, 221, 221, 153, 154, 170, 0, 10, 153, 153, 154, 170, 0, 0, 0, 10, 169, 153,
1, 3, 51, 51, 51, 51, 49, 0, 16, 51, 51, 51, 48, 17, 32, 1, 3, 51, 51, 51, 32, 1, 0, 32, 51, 192, 51, 48, 3, 16, 1, 3, 59, 3, 192, 51, 49, 0, 240, 60, 188, 11, 3, 51, 240, 17, 27, 188, 188, 187, 3, 17, 29, 221, 221, 221, 221, 221, 220, 17, 153, 153, 170, 169, 153, 153, 221, 217, 154, 160, 0, 170, 170, 170, 153,
0, 17, 17, 17, 17, 17, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 51, 51, 51, 51, 51, 51, 48, 3, 3, 51, 48, 51, 48, 51, 0, 0, 48, 3, 3, 0, 0, 0, 0, 0, 0, 48, 0, 0, 0, 32, 68, 132, 68, 132, 68, 132, 65, 45, 221, 221, 221, 221, 221, 221, 221, 154, 169, 153, 153, 154, 169, 153, 154, 0, 169, 153, 154, 0, 169,
17, 17, 17, 17, 16, 51, 51, 16, 0, 0, 0, 0, 3, 49, 17, 51, 51, 51, 51, 51, 49, 17, 35, 51, 3, 48, 51, 17, 17, 17, 48, 0, 0, 3, 0, 0, 0, 16, 0, 4, 72, 68, 64, 51, 49, 72, 68, 221, 221, 221, 68, 3, 29, 221, 217, 169, 153, 157, 212, 2, 154, 153, 160, 169, 169, 153, 212, 26, 10, 160, 0, 160, 170, 154, 209
};



typedef struct {
unsigned char np, x, y, st;
} CERROJOS;

CERROJOS cerrojos [4] = {
{5, 6, 8, 0},
{25, 8, 5, 0},
{27, 1, 5, 0},
{27, 13, 5, 0}
};
# 4 "assets/tileset.h"
extern unsigned char tileset [0];
#asm

XDEF _ts
XDEF tiles
._tileset
.tiles
._font
BINARY "../bin/font.bin"
._tspatterns
BINARY "../bin/work.bin"
#endasm
# 7 "assets/enems.h"
typedef struct {
unsigned char x, y;
unsigned char x1, y1, x2, y2;
char mx, my;
char t;
# 15
} MALOTE;

MALOTE malotes [] = {

{64, 16, 64, 16, 64, 128, 0, 4, 3},
{208, 16, 208, 16, 96, 16, -2, 0, 0},
{192, 0, 192, 0, 112, 0, -2, 0, 0},


{128, 0, 128, 0, 128, 64, 0, 1, 2},
{144, 16, 144, 16, 176, 96, 2, 2, 2},
{48, 64, 48, 64, 48, 128, 0, 1, 4},


{16, 32, 16, 32, 96, 32, 2, 0, 1},
{144, 96, 144, 96, 144, 0, 0, -1, 3},
{176, 0, 176, 0, 176, 80, 0, 1, 2},


{96, 112, 96, 112, 48, 112, -1, 0, 3},
{48, 0, 48, 0, 48, 32, 0, 1, 1},
{208, 0, 208, 0, 208, 64, 0, 2, 1},


{64, 0, 64, 0, 64, 80, 0, 1, 1},
{96, 0, 96, 0, 96, 64, 0, 1, 1},
{160, 0, 160, 0, 208, 80, 2, 2, 2},


{80, 112, 80, 112, 16, 112, -2, 0, 2},
{96, 0, 96, 0, 0, 0, -1, 0, 2},
{224, 0, 224, 0, 224, 48, 0, 1, 2},


{192, 48, 192, 48, 128, 48, -1, 0, 4},
{160, 16, 160, 16, 160, 96, 0, 2, 1},
{16, 96, 16, 96, 80, 128, 4, 4, 2},


{16, 80, 16, 80, 96, 48, 1, -1, 1},
{16, 16, 16, 16, 96, 16, 2, 0, 2},
{160, 0, 160, 0, 160, 144, 0, 2, 3},


{48, 32, 48, 32, 144, 32, 2, 0, 3},
{112, 48, 112, 48, 112, 128, 0, 1, 2},
{160, 96, 160, 96, 160, 0, 0, -2, 3},


{96, 128, 96, 128, 96, 16, 0, -2, 4},
{144, 16, 144, 16, 176, 112, 2, 2, 3},
{112, 48, 112, 48, 32, 16, -2, -2, 1},


{64, 128, 64, 128, 208, 128, 1, 0, 4},
{208, 112, 208, 112, 112, 112, -1, 0, 1},
{64, 16, 64, 16, 96, 16, 1, 0, 3},


{16, 128, 16, 128, 160, 128, 1, 0, 4},
{48, 112, 48, 112, 48, 64, 0, -1, 4},
{80, 48, 80, 48, 160, 96, 2, 2, 2},


{208, 112, 208, 112, 128, 112, -1, 0, 3},
{208, 80, 208, 80, 208, 16, 0, -1, 2},
{16, 16, 16, 16, 96, 128, 4, 4, 3},


{64, 0, 64, 0, 112, 48, 2, 2, 1},
{16, 64, 16, 64, 80, 112, 1, 1, 2},
{208, 16, 208, 16, 192, 128, -2, 2, 3},


{16, 0, 16, 0, 112, 32, 1, 1, 2},
{208, 0, 208, 0, 176, 48, -2, 2, 3},
{64, 64, 64, 64, 96, 0, 1, -1, 1},


{160, 112, 160, 112, 160, 64, 0, -1, 4},
{192, 32, 192, 32, 48, 32, -1, 0, 4},
{64, 0, 64, 0, 176, 16, 1, 1, 3},


{192, 48, 192, 48, 80, 48, -1, 0, 4},
{112, 32, 112, 32, 176, 32, 1, 0, 3},
{64, 80, 64, 80, 192, 112, 2, 2, 2},


{192, 48, 192, 48, 32, 48, -1, 0, 4},
{16, 32, 16, 32, 128, 32, 1, 0, 1},
{16, 64, 16, 64, 112, 112, 2, 2, 2},


{208, 64, 208, 64, 128, 64, -1, 0, 2},
{48, 16, 48, 16, 48, 80, 0, 2, 1},
{64, 32, 64, 32, 64, 80, 0, 2, 3},


{16, 112, 16, 112, 112, 112, 1, 0, 1},
{192, 128, 192, 128, 192, 16, 0, -1, 4},
{112, 48, 112, 48, 16, 48, -2, 0, 3},


{176, 48, 176, 48, 32, 48, -1, 0, 1},
{176, 64, 176, 64, 48, 64, -1, 0, 1},
{16, 0, 16, 0, 192, 32, 2, 2, 2},


{32, 112, 32, 112, 192, 112, 2, 0, 4},
{192, 32, 192, 32, 48, 32, -2, 0, 4},
{176, 80, 176, 80, 48, 80, -1, 0, 1},


{208, 80, 208, 80, 32, 80, -1, 0, 4},
{64, 64, 64, 64, 176, 64, 1, 0, 2},
{16, 0, 16, 0, 0, 144, -3, 3, 2},


{16, 48, 16, 48, 208, 48, 1, 0, 4},
{96, 64, 96, 64, 96, 128, 0, 1, 1},
{208, 80, 208, 80, 128, 128, -2, 2, 3},


{96, 32, 96, 32, 96, 96, 0, 2, 6},
{128, 80, 128, 80, 224, 80, 2, 0, 4},
{96, 112, 96, 112, 16, 112, -1, 0, 3},


{112, 16, 112, 16, 112, 80, 0, 1, 2},
{48, 96, 48, 96, 48, 0, 0, -2, 1},
{176, 48, 176, 48, 176, 128, 0, 2, 3},


{160, 32, 160, 32, 192, 80, 2, 2, 1},
{96, 48, 96, 48, 96, 0, 0, -1, 2},
{144, 144, 144, 144, 48, 144, -1, 0, 3},


{32, 80, 32, 80, 32, 16, 0, -2, 1},
{192, 80, 192, 80, 192, 32, 0, -2, 2},
{112, 80, 112, 80, 112, 32, 0, -1, 3},


{208, 48, 208, 48, 32, 48, -1, 0, 4},
{64, 32, 64, 32, 192, 32, 1, 0, 2},
{80, 96, 80, 96, 112, 96, 1, 0, 1},


{112, 16, 112, 16, 16, 80, -2, 2, 3},
{176, 64, 176, 64, 176, 96, 0, 1, 1},
{208, 80, 208, 80, 208, 128, 0, 1, 1}

};
# 182
typedef struct {
unsigned char xy, tipo, act;
} HOTSPOT;

HOTSPOT hotspots [] = {
{22, 2, 0},
{120, 2, 0},
{113, 1, 0},
{216, 1, 0},
{81, 1, 0},
{24, 1, 0},
{98, 1, 0},
{115, 1, 0},
{69, 1, 0},
{129, 2, 0},
{209, 2, 0},
{18, 1, 0},
{200, 1, 0},
{100, 1, 0},
{148, 1, 0},
{34, 1, 0},
{66, 1, 0},
{209, 1, 0},
{19, 1, 0},
{113, 1, 0},
{133, 1, 0},
{35, 1, 0},
{70, 1, 0},
{87, 1, 0},
{129, 1, 0},
{87, 1, 0},
{114, 1, 0},
{100, 1, 0},
{129, 1, 0},
{212, 1, 0}
};
# 8 "assets/sprites.h"
extern unsigned char sprites [0];
#asm


._sprites
BINARY "../bin/sprites.bin"
#endasm
# 15 "assets/extrasprites.h"
extern unsigned char sprite_18_a [];


extern unsigned char sprite_19_a [];
extern unsigned char sprite_19_b [];
#asm
#endasm
#asm
# 30
._sprite_18_a
defs 96, 0
#endasm
#asm




._sprite_19_a
BINARY "../bin/sprites_bullet.bin"
#endasm
# 9 "assets/spriteset_mappings.h"
unsigned char sm_cox [] = {
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char sm_coy [] = {
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0
};

void *sm_invfunc [] = {
cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16,
cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16,
cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16,
cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16, cpc_PutSpTileMap8x16
};

void *sm_updfunc [] = {
cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b,
cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b, cpc_PutTrSp8x16TileMap2b
};

extern void *sm_sprptr [0];
#asm

._sm_sprptr
defw _sprites + 0x000, _sprites + 0x040, _sprites + 0x080, _sprites + 0x0C0
defw _sprites + 0x100, _sprites + 0x140, _sprites + 0x180, _sprites + 0x1C0
defw _sprites + 0x200, _sprites + 0x240, _sprites + 0x280, _sprites + 0x2C0
defw _sprites + 0x300, _sprites + 0x340, _sprites + 0x380, _sprites + 0x3C0
#endasm
# 4 "assets/trpixlut.h"
extern unsigned char trpixlutc [0];
#asm


; LUT for transparent pixels in sprites
; taken from CPCTelera
._trpixlutc
BINARY "assets/trpixlutc.bin"
#endasm
# 6 "printer.h"
unsigned char attr (unsigned char x, unsigned char y) {
if (x >= 14 || y >= 10) return 0;
return map_attr [x + (y << 4) - y];
}

unsigned char qtile (unsigned char x, unsigned char y) {
return map_buff [x + (y << 4) - y];
}
#asm
#endasm
# 57
void _tile_address (void) {
#asm

ld a, (__y)

add a, a ; 2 4
add a, a ; 4 4
add a, a ; 8 4
ld h, 0 ; 2
ld l, a ; 4
add hl, hl ; 16 11
add hl, hl ; 32 11
; 44 t-states

; HL = _y * 32

ld a, (__x)
ld e, a
ld d, 0
add hl, de

; HL = _y * 32 + _x

ld de, _nametable
add hl, de

ex de, hl

; DE = buffer address
#endasm

}

void draw_coloured_tile (void) {
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
# 350
call __tile_address ; DE = buffer address
ex de, hl


ld a, (__t)
sla a
sla a
add 64

ld (hl), a
inc hl
inc a
ld (hl), a
ld bc, 31
add hl, bc
inc a
ld (hl), a
inc hl
inc a
ld (hl), a
#endasm


}

void invalidate_tile (void) {
#asm


ld a, (__x)
ld e, a
ld a, (__y)
ld d, a
call cpc_UpdTileTable
inc e
call cpc_UpdTileTable
dec e
inc d
call cpc_UpdTileTable
inc e
call cpc_UpdTileTable
#endasm

}

void invalidate_viewport (void) {
#asm

ld B, 2
ld C, 1
ld D, 2+19
ld E, 1+29
call cpc_InvalidateRect
#endasm

}

void draw_invalidate_coloured_tile_g (void) {
draw_coloured_tile_gamearea ();
invalidate_tile ();
}

void draw_coloured_tile_gamearea (void) {
_x = 1 + (_x << 1); _y = 2 + (_y << 1); draw_coloured_tile ();
}

void draw_decorations (void) {
#asm


ld hl, (__gp_gen)

._draw_decorations_loop
ld a, (hl)
cp 0xff
ret z

ld a, (hl)
inc hl
ld c, a
and 0x0f
ld (__y), a
ld a, c
srl a
srl a
srl a
srl a
ld (__x), a

ld a, (hl)
inc hl
ld (__t), a

push hl

ld b, 0
ld c, a
ld hl, _behs
add hl, bc
ld a, (hl)
ld (__n), a

call _update_tile

pop hl
jr _draw_decorations_loop
#endasm

}

unsigned char utaux = 0;
void update_tile (void) {
#asm
# 469
ld a, (__x)
ld c, a
ld a, (__y)
ld b, a
sla a
sla a
sla a
sla a
sub b
add c
ld b, 0
ld c, a
ld hl, _map_attr
add hl, bc
ld a, (__n)
ld (hl), a
ld hl, _map_buff
add hl, bc
ld a, (__t)
ld (hl), a

call _draw_coloured_tile_gamearea

ld a, (_is_rendering)
or a
ret nz

call _invalidate_tile
#endasm

}

void print_number2 (void) {
rda = 16 + (_t / 10); rdb = 16 + (_t % 10);
#asm

call __tile_address ; DE = buffer address
ld a, (_rda)
ld (de), a
inc de
ld a, (_rdb)
ld (de), a

ld a, (__x)
ld e, a
ld a, (__y)
ld d, a
call cpc_UpdTileTable
inc e
call cpc_UpdTileTable
#endasm

}


void draw_objs () {
#asm
#endasm
# 573
_x = 30; _y = 0;



_t = p_objs;

print_number2 ();


}


void print_str (void) {
#asm

call __tile_address ; DE = buffer address
ld hl, (__gp_gen)

.print_str_loop
ld a, (hl)
or a
ret z

sub 32
ld (de), a

inc hl
inc de

jr print_str_loop
#endasm

}
# 611
void clear_sprites (void) {
#asm
#endasm


}

void pal_set (unsigned char *pal) {

gpit = 16;
# 622
while (gpit --) cpc_SetColour (gpit, pal[gpit]);
}
# 6 "engine/general.h"
unsigned char collide (void) {

return (gpx + 8 >= cx2 && gpx <= cx2 + 8 && gpy + 8 >= cy2 && gpy <= cy2 + 8);
# 12
}

unsigned char cm_two_points (void) {
#asm
# 23
ld a, (_cx1)
cp 15
jr nc, _cm_two_points_at1_reset

ld a, (_cy1)
cp 10
jr c, _cm_two_points_at1_do

._cm_two_points_at1_reset
xor a
jr _cm_two_points_at1_done

._cm_two_points_at1_do
ld a, (_cy1)
ld b, a
sla a
sla a
sla a
sla a
sub b
ld b, a
ld a, (_cx1)
add b
ld e, a
ld d, 0
ld hl, _map_attr
add hl, de
ld a, (hl)

._cm_two_points_at1_done
ld (_at1), a

ld a, (_cx2)
cp 15
jr nc, _cm_two_points_at2_reset

ld a, (_cy2)
cp 10
jr c, _cm_two_points_at2_do

._cm_two_points_at2_reset
xor a
jr _cm_two_points_at2_done

._cm_two_points_at2_do
ld a, (_cy2)
ld b, a
sla a
sla a
sla a
sla a
sub b
ld b, a
ld a, (_cx2)
add b
ld e, a
ld d, 0
ld hl, _map_attr
add hl, de
ld a, (hl)

._cm_two_points_at2_done
ld (_at2), a
#endasm

}

unsigned char rand (void) {
#asm

.rand16
ld hl, _seed
ld a, (hl)
ld e, a
inc hl
ld a, (hl)
ld d, a

;; Ahora DE = [SEED]

ld a, d
ld h, e
ld l, 253
or a
sbc hl, de
sbc a, 0
sbc hl, de
ld d, 0
sbc a, d
ld e, a
sbc hl, de
jr nc, nextrand
inc hl
.nextrand
ld d, h
ld e, l
ld hl, _seed
ld a, e
ld (hl), a
inc hl
ld a, d
ld (hl), a

;; Ahora [SEED] = HL

ld l, e
ret
#endasm

}

unsigned int abs (signed int n) {
if (n < 0)
return (unsigned int) (-n);
else
return (unsigned int) n;
}


void step (void) {
#asm

ld a, 16
out (254), a
nop
nop
nop
nop
nop
nop
nop
nop
nop
xor 16
out (254), a
#endasm

}


void cortina (void) {
#asm
#endasm


}
# 12 "engine/simple_cocos.h"
void simple_coco_init (void) {
for (enit = 0; enit < 3; ++ enit) cocos_y [enit] = 0xff;
}

void simple_coco_shoot (void) {
#asm

ld de, (_enit)
ld d, 0

ld hl, _cocos_y
add hl, de

ld a, (hl)
cp 160
ret c

ld a, (__en_y)
add 4
ld (hl), a

ld hl, _cocos_x
add hl, de
ld a, (__en_x)
add 4
ld (hl), a

ld a, (_rda)

ld e, a
ld d, 0
ld hl, __dx
add hl, de
ld b, (hl)
ld hl, __dy
add hl, de
ld c, (hl)

ld de, (_enit)
ld d, 0

ld hl, _cocos_mx
add hl, de
ld (hl), b

ld hl, _cocos_my
add hl, de
ld (hl), c
#endasm

}

void simple_coco_update (void) {
enspit = 1 + 3 + 0;
for (enit = 0; enit < 3; ++ enit) {
if (cocos_y [enit] < 160) {
#asm

._simple_coco_update_do


ld de, (_enit)
ld d, 0

ld hl, _cocos_y
add hl, de
ld b, (hl)

ld hl, _cocos_x
add hl, de
ld c, (hl)

ld hl, _cocos_my
add hl, de
ld a, (hl)
add b
ld (_rdy), a

ld hl, _cocos_mx
add hl, de
ld a, (hl)
add c
ld (_rdx), a


cp 240
jr c, _simple_coco_update_keep_going

ld a, 0xff
ld (_rdy), a
jp _simple_coco_update_continue

._simple_coco_update_keep_going
#endasm
#asm
# 124
ld a, (_gpx)
ld c, a
ld a, (_rdx)
add 3
cp c
jr c, _simple_coco_update_collpl_done


ld a, (_rdx)
ld c, a
ld a, (_gpx)
add 12
cp c
jr c, _simple_coco_update_collpl_done
# 143
ld a, (_gpy)
ld c, a
ld a, (_rdy)
add 3
cp c
jr c, _simple_coco_update_collpl_done


ld a, (_rdy)
ld c, a
ld a, (_gpy)
add 12
cp c
jr c, _simple_coco_update_collpl_done


ld a, 0xff
ld (_rdy), a




ld a, 4

ld (_p_killme), a

jr _simple_coco_update_continue

._simple_coco_update_collpl_done
#endasm




if (attr ((rdx + 3) >> 4, (rdy + 3) >> 4) & 12) rdy = 0xff;
#asm



._simple_coco_update_continue

ld de, (_enit)
ld d, 0

ld hl, _cocos_y
add hl, de
ld a, (_rdy)
ld (hl), a

ld hl, _cocos_x
add hl, de
ld a, (_rdx)
ld (hl), a

._simple_coco_update_done
#endasm

} else {
# 203
}
++ enspit;
}
}
# 4 "my/fixed_screens.h"
void game_ending (void) {
blackout ();
#asm
# 11
ld hl, _s_ending
ld de, 0x9000
call depack
#endasm


cpc_ShowTileMap (1);

espera_activa (500);
}

void game_over (void) {
_x = 10; _y = 11; _t = 79; _gp_gen = spacer; print_str ();
_x = 10; _y = 12; _t = 79; _gp_gen = " GAME OVER! "; print_str ();
_x = 10; _y = 13; _t = 79; _gp_gen = spacer; print_str ();

cpc_ShowTileMap (0);

espera_activa (500);
}
# 16 "engine.h"
signed int addsign (signed int n, signed int value) {
if (n >= 0) return value; else return -value;
}
# 24
void espera_activa (int espera) {
while (cpc_AnyKeyPressed ());
do {
#asm

halt
halt
halt
halt
halt
halt
#endasm

if (cpc_AnyKeyPressed ()) break;
} while (-- espera);
}



void locks_init (void) {
for (gpit = 0; gpit < 4; ++ gpit) cerrojos [gpit].st = 1;
}
# 68
void process_tile (void) {
# 109
if (qtile (x0, y0) == 15 && p_keys) {
for (gpit = 0; gpit < 4; ++ gpit) {
if (cerrojos [gpit].x == x0 && cerrojos [gpit].y == y0 && cerrojos [gpit].np == n_pant) {
cerrojos [gpit].st = 0;
break;
}
}
_x = x0; _y = y0; _t = 0; _n = 0; update_tile ();
-- p_keys;

;;
# 122
}

}


void draw_scr_background (void) {



map_pointer = mapa + (n_pant * 75);


seed = n_pant;

_x = 1; _y = 2;
# 143
for (gpit = 0; gpit < 150; ++ gpit) {
#asm
#endasm
#asm
# 189
ld a, (_gpit)
and 1
jr nz, _draw_scr_packed_existing
._draw_scr_packed_new
ld hl, (_map_pointer)
ld a, (hl)
ld (_gpc), a
inc hl
ld (_map_pointer), hl

srl a
srl a
srl a
srl a
jr _draw_scr_packed_done

._draw_scr_packed_existing
ld a, (_gpc)
and 15

._draw_scr_packed_done
ld (__t), a

ld b, 0
ld c, a
ld hl, _behs
add hl, bc
ld a, (hl)

ld bc, (_gpit)
ld b, 0
ld hl, _map_attr
add hl, bc
ld (hl), a


ld a, (__t)
or a
jr nz, _draw_scr_packed_noalt

._draw_scr_packed_alt
call _rand
ld a, l
and 15
cp 1
jr z, _draw_scr_packed_alt_subst

ld a, (__t)
jr _draw_scr_packed_noalt

._draw_scr_packed_alt_subst
ld a, 19
ld (__t), a

._draw_scr_packed_noalt


ld hl, _map_buff
add hl, bc

ld (hl), a
#endasm
#asm
#endasm
# 263
draw_coloured_tile ();
#asm
# 274
ld a, (__x)
add 2
cp 30 + 1
jr c, _advance_worm_no_inc_y

ld a, (__y)
add 2
ld (__y), a

ld a, 1

._advance_worm_no_inc_y
ld (__x), a
#endasm

}

}

void draw_scr (void) {

cpc_ResetTouchedTiles ();

is_rendering = 1;
# 306
draw_scr_background ();



enems_load ();
#asm
# 337
ld a, 240
ld (_hotspot_y), a




ld a, (_n_pant)
ld b, a
sla a
add b

ld c, a
ld b, 0



ld hl, _hotspots
add hl, bc



ld a, (hl)
ld b, a

srl a
srl a
srl a
srl a
ld (__x), a

ld a, b
and 15
ld (__y), a

inc hl
ld b, (hl)
inc hl
ld c, (hl)



xor a
or b
jr z, _hotspots_setup_done

xor a
or c
jr z, _hotspots_setup_done

._hotspots_setup_do
ld a, (__x)
ld e, a
sla a
sla a
sla a
sla a
ld (_hotspot_x), a

ld a, (__y)
ld d, a
sla a
sla a
sla a
sla a
ld (_hotspot_y), a



sub d
add e

ld e, a
ld d, 0
ld hl, _map_buff
add hl, de
ld a, (hl)
ld (_orig_tile), a


ld a, b
cp 3
jp nz, _hotspots_setup_set

._hotspots_setup_set_refill
xor a
._hotspots_setup_set
add 16
ld (__t), a

call _draw_coloured_tile_gamearea

._hotspots_setup_done
#endasm
#asm
# 447
ld hl, _cerrojos
ld b, 4
._open_locks_loop
push bc

ld a, (_n_pant)
ld c, a

ld b, (hl)
inc hl

ld d, (hl)
inc hl

ld e, (hl)
inc hl

ld a, (hl)
inc hl

or a
jr nz, _open_locks_done

ld a, b
cp c
jr nz, _open_locks_done

._open_locks_do
ld a, d
ld (__x), a
ld a, e
ld (__y), a

sla a
sla a
sla a
sla a
sub e
add d

ld b, 0
ld c, a
xor a

push hl

ld hl, _map_attr
add hl, bc
ld (hl), a
ld hl, _map_buff
add hl, bc
ld (hl), a

ld (__t), a

call _draw_coloured_tile_gamearea

pop hl

._open_locks_done

pop bc
dec b
jr nz, _open_locks_loop
#endasm
# 519
simple_coco_init ();


invalidate_viewport ();
is_rendering = 0;
}

void select_joyfunc (void) {
}
# 6 "engine/player.h"
void player_init (void) {




gpx = 2 << 4; p_x = gpx << 6;
gpy = 2 << 4; p_y = gpy << 6;

p_vy = 0;
p_vx = 0;
p_cont_salto = 1;
p_saltando = 0;
p_frame = 0;
p_subframe = 0;




p_facing = 1;

p_estado = 0;
p_ct_estado = 0;

p_life = 99;

p_objs = 0;
p_keys = 0;
p_killed = 0;
p_disparando = 0;
# 58
}

void player_calc_bounding_box (void) {
#asm


ld a, (_gpx)
add 4
srl a
srl a
srl a
srl a
ld (_ptx1), a
ld a, (_gpx)
add 11
srl a
srl a
srl a
srl a
ld (_ptx2), a
ld a, (_gpy)
add 8
srl a
srl a
srl a
srl a
ld (_pty1), a
ld a, (_gpy)
add 15
srl a
srl a
srl a
srl a
ld (_pty2), a
#endasm
#asm
#endasm
#asm
#endasm
# 153
}

unsigned char player_move (void) {
# 167
{
#asm



; Signed comparisons are hard
; p_vy <= 512 - 32

; We are going to take a shortcut.
; If p_vy < 0, just add 32.
; If p_vy > 0, we can use unsigned comparition anyway.

ld hl, (_p_vy)
bit 7, h
jr nz, _player_gravity_add ; < 0

ld de, 512 - 32
or a
push hl
sbc hl, de
pop hl
jr nc, _player_gravity_maximum

._player_gravity_add
ld de, 32
add hl, de
jr _player_gravity_vy_set

._player_gravity_maximum
ld hl, 512

._player_gravity_vy_set
ld (_p_vy), hl

._player_gravity_done
# 208
ld a, (_p_gotten)
or a
jr z, _player_gravity_p_gotten_done

xor a
ld (_p_vy), a

._player_gravity_p_gotten_done
#endasm

}
# 271
p_y += p_vy;


if (p_gotten) p_y += ptgmy;




if (p_y < 0) p_y = 0;
if (p_y > 9216) p_y = 9216;

gpy = p_y >> 6;



player_calc_bounding_box ();

hit_v = 0;
cx1 = ptx1; cx2 = ptx2;



if (p_vy + ptgmy < 0)

{
cy1 = cy2 = pty1;
cm_two_points ();

if ((at1 & 8) || (at2 & 8)) {
# 305
p_vy = 0;



gpy = ((pty1 + 1) << 4) - 8;
# 318
p_y = gpy << 6;
# 323
}
}




if (p_vy + ptgmy > 0)

{
cy1 = cy2 = pty2;
cm_two_points ();
# 340
if ((at1 & 8) || (at2 & 8) || (((gpy - 1) & 15) < 8 && ((at1 & 4) || (at2 & 4))))


{
# 349
p_vy = 0;



gpy = (pty2 - 1) << 4;
# 360
p_y = gpy << 6;
# 365
}
}


if (p_vy) hit_v = ((at1 & 1) || (at2 & 1));


gpxx = gpx >> 4;
gpyy = gpy >> 4;


cy1 = cy2 = (gpy + 16) >> 4;
cx1 = ptx1; cx2 = ptx2;
cm_two_points ();
possee = ((at1 & 12) || (at2 & 12)) && (gpy & 15) < 8;
# 388
{
# 394
rda = cpc_TestKey (4);


if (rda) {
if (p_saltando == 0) {
if (possee || p_gotten || hit_v) {
p_saltando = 1;
p_cont_salto = 0;
;;
}
} else {
p_vy -= (64 + 64 - (p_cont_salto >> 1));
if (p_vy < -320) p_vy = -320;
++ p_cont_salto;
if (p_cont_salto == 9) p_saltando = 0;
}
} else p_saltando = 0;
}
# 442
if ( ! (cpc_TestKey (0) || cpc_TestKey (1))) {
# 446
if (p_vx > 0) {
p_vx -= 32;
if (p_vx < 0) p_vx = 0;
} else if (p_vx < 0) {
p_vx += 32;
if (p_vx > 0) p_vx = 0;
}
wall_h = 0;
}

if (cpc_TestKey (0)) {
# 460
if (p_vx > -192) {

p_facing = 0;

p_vx -= 24;
}
}

if (cpc_TestKey (1)) {
# 472
if (p_vx < 192) {
p_vx += 24;

p_facing = 1;

}
}
# 483
p_x = p_x + p_vx;

p_x += ptgmx;




if (p_x < 0) p_x = 0;
if (p_x > 14336) p_x = 14336;

gpox = gpx;
gpx = p_x >> 6;


player_calc_bounding_box ();

hit_h = 0;
cy1 = pty1; cy2 = pty2;




if (p_vx + ptgmx < 0)

{
cx1 = cx2 = ptx1;
cm_two_points ();

if ((at1 & 8) || (at2 & 8)) {
# 517
p_vx = 0;



gpx = ((ptx1 + 1) << 4) - 4;
# 526
p_x = gpx << 6;
wall_h = 3;
}

else hit_h = ((at1 & 1) || (at2 & 1));


}




if (p_vx + ptgmx > 0)

{
cx1 = cx2 = ptx2;
cm_two_points ();

if ((at1 & 8) || (at2 & 8)) {
# 550
p_vx = 0;



gpx = (ptx1 << 4) + 4;
# 559
p_x = gpx << 6;
wall_h = 4;
}

else hit_h = ((at1 & 1) || (at2 & 1));


}
# 586
cx1 = p_tx = (gpx + 8) >> 4;
cy1 = p_ty = (gpy + 8) >> 4;

rdb = attr (cx1, cy1);


if (rdb & 128) {
# 594
}
# 630
if (wall_h == 3) {


cx1 = (gpx + 3) >> 4;
# 638
if (attr (cx1, cy1) == 10) {
y0 = y1 = cy1; x0 = cx1; x1 = cx1 - 1;
process_tile ();
}
} else if (wall_h == 4) {


cx1 = (gpx + 12) >> 4;
# 649
if (attr (cx1, cy1) == 10) {
y0 = y1 = cy1; x0 = cx1; x1 = cx1 + 1;
process_tile ();
}
}
# 677
hit = 0;
if (hit_v) {
hit = 1;
p_vy = addsign (-p_vy, 192);
} else if (hit_h) {
hit = 1;
p_vx = addsign (-p_vx, 192);
}

if (hit) {
# 690
{



p_killme = 4;

}
}
# 729
if (!possee && !p_gotten) {
gpit = p_facing ? 3 : 7;
} else {
gpit = p_facing ? 0 : 4;
if (p_vx == 0) {
++ gpit;
} else {
rda = ((gpx + 4) >> 3) & 3;
if (rda == 3) rda = 1;
gpit += rda;
}

}

sp_sw [0].sp0 = (int) (sm_sprptr [gpit]);


sp_sw [0].cx = (gpx + 1*8 + sp_sw [0].cox) >> 2;
sp_sw [0].cy = (gpy + 2*8 + sp_sw [0].coy);

if ( (p_estado & 2) && half_life ) sp_sw [0].sp0 = (int) (sprite_18_a);
}

void player_deplete (void) {
p_life = (p_life > p_kill_amt) ? p_life - p_kill_amt : 0;
}

void player_kill (unsigned char sound) {
p_killme = 0;

player_deplete ();

;;
# 778
}
# 28 "engine/enengine.h"
void enems_load (void) {

enoffs = n_pant * 3;

for (enit = 0; enit < 3; ++ enit) {
en_an_frame [enit] = 0;
en_an_state [enit] = 0;
en_an_count [enit] = 3;
enoffsmasi = enoffs + enit;
# 50
en_an_next_frame [enit] = sprite_18_a;

rdt = malotes [enoffsmasi].t & 0x1f;
if (rdt) {
switch (rdt) {
case 1:
case 2:
case 3:
case 4:
en_an_base_frame [enit] = 8 + ((malotes [enoffsmasi].t - 1) << 1);
break;


case 5:



en_an_base_frame [enit] = 8 + (0 << 1);

en_an_state [enit] = malotes [enoffsmasi].t >> 6;
break;
# 97
default:
en_an_base_frame [enit] = 0xff;
}
} else {
en_an_base_frame [enoffsmasi] = 0xff;
}



rda = 1 + enit;
if (rdb = en_an_base_frame [enit] != 0xff) {
sp_sw [rda].cox = sm_cox [rdb];
sp_sw [rda].coy = sm_coy [rdb];
sp_sw [rda].invfunc = sm_invfunc [rdb];
sp_sw [rda].updfunc = sm_updfunc [rdb];
en_an_next_frame [enit] = sm_sprptr [rdb];
} else {
en_an_next_frame [enit] = sprite_18_a;
sp_sw [rda].invfunc = cpc_PutSpTileMap4x8;
sp_sw [rda].updfunc = cpc_PutTrSp4x8TileMap2b;
}
# 120
}
}

void enems_kill (void) {
if (_en_t != 7) _en_t |= 16;
++ p_killed;
# 136
}

void enems_move (void) {
tocado = p_gotten = ptgmx = ptgmy = 0;

for (enit = 0; enit < 3; enit ++) {
active = 0;
enoffsmasi = enoffs + enit;
#asm
# 152
ld hl, (_enoffsmasi)
ld h, 0
# 164
ld d, h
ld e, l
add hl, hl
add hl, hl
add hl, hl

add hl, de


ld de, _malotes
add hl, de

ld (__baddies_pointer), hl

ld a, (hl)
ld (__en_x), a
inc hl

ld a, (hl)
ld (__en_y), a
inc hl

ld a, (hl)
ld (__en_x1), a
inc hl

ld a, (hl)
ld (__en_y1), a
inc hl

ld a, (hl)
ld (__en_x2), a
inc hl

ld a, (hl)
ld (__en_y2), a
inc hl

ld a, (hl)
ld (__en_mx), a
inc hl

ld a, (hl)
ld (__en_my), a
inc hl

ld a, (hl)
ld (__en_t), a
and 0x1f
ld (_rdt), a
#endasm
# 227
if (en_an_state [enit] == 4) {
-- en_an_count [enit];
if (en_an_count [enit] == 0) {
en_an_state [enit] = 0;
en_an_next_frame [enit] = sprite_18_a;
continue;
}
}



pregotten = (gpx + 12 >= _en_x && gpx <= _en_x + 12);
# 244
switch (rdt) {
case 1:
case 2:
case 3:
case 4:

case 5:
#asm
# 21 "./engine/enem_mods/enem_type_lineal.h"
ld a, 1
ld (_active), a

ld a, (__en_mx)
ld c, a
ld a, (__en_x)
add a, c
ld (__en_x), a

ld c, a
ld a, (__en_x1)
cp c
jr z, _enems_lm_change_axis_x
ld a, (__en_x2)
cp c
# 46
jr nz, _enems_lm_change_axis_x_done


._enems_lm_change_axis_x
ld a, (__en_mx)
neg
ld (__en_mx), a

._enems_lm_change_axis_x_done

ld a, (__en_my)
ld c, a
ld a, (__en_y)
add a, c
ld (__en_y), a

ld c, a
ld a, (__en_y1)
cp c
jr z, _enems_lm_change_axis_y
ld a, (__en_y2)
cp c
# 78
jr nz, _enems_lm_change_axis_y_done


._enems_lm_change_axis_y
ld a, (__en_my)
neg
ld (__en_my), a

._enems_lm_change_axis_y_done
#endasm
# 254 "engine/enengine.h"
if (rdt == 5) {
# 6 "./engine/enem_mods/enem_type_orthoshooters.h"
if ((rand()&15) == 1) {
rda = en_an_state [enit];
simple_coco_shoot ();
}
# 256 "engine/enengine.h"
}

break;
# 275
}

if (active) {

if (en_an_base_frame [enit] != 99) {
#asm
# 290
ld bc, (_enit)
ld b, 0

ld hl, _en_an_count
add hl, bc
ld a, (hl)
inc a
ld (hl), a

cp 4
jr nz, _enems_move_update_frame_done

xor a
ld (hl), a

ld hl, _en_an_frame
add hl, bc
ld a, (hl)
xor 1
ld (hl), a

ld hl, _en_an_base_frame
add hl, bc
ld d, (hl)
add d ; A = en_an_base_frame [enit] + en_an_frame [enit]]

sla c ; Index 16 bits; it never overflows.
ld hl, _en_an_next_frame
add hl, bc
ex de, hl ; DE -> en_an_next_frame [enit]

sla a
ld c, a
ld b, 0

ld hl, _sm_sprptr
add hl, bc ; HL -> enem_cells [en_an_base_frame [enit] + en_an_frame [enit]]

ldi
ldi ; Copy 16 bit
._enems_move_update_frame_done
#endasm


}
# 339
if (_en_t == 4) {
if (pregotten) {


if (_en_mx) {
if (gpy + 17 >= _en_y && gpy + 8 <= _en_y) {
p_gotten = 1;
ptgmx = _en_mx << 6;
gpy = (_en_y - 16); p_y = gpy << 6;
}
}


if (
(_en_my < 0 && gpy + 18 >= _en_y && gpy + 8 <= _en_y) ||
(_en_my > 0 && gpy + 17 + _en_my >= _en_y && gpy + 8 <= _en_y)
) {
p_gotten = 1;
ptgmy = _en_my << 6;
gpy = (_en_y - 16); p_y = gpy << 6;
}

}
} else

{
# 367
cx2 = _en_x; cy2 = _en_y;
if (!tocado && collide () && p_estado == 0) {
# 387
{
tocado = 1;
# 402
p_killme = 4;
# 415
{
p_vx = addsign (_en_mx, 192);
p_vy = addsign (_en_my, 192);
}
# 432
}
}
}
player_enem_collision_done:
# 484
}

rda = 1 + enit; rdt = en_an_sprid [enit];
sp_sw [rda].cx = (malotes [enoffsmasi].x + 1 * 8 + sm_cox [rdt]) >> 2;
sp_sw [rda].cy = (malotes [enoffsmasi].y + 2 * 8 + sm_coy [rdt]);
if (rdt != 0xff) sp_sw [rda].sp0 = (int) (en_an_next_frame [enit]);
else sp_sw [rda].sp0 = (int) (sprite_18_a);
#asm
# 496
ld hl, (__baddies_pointer)

ld a, (__en_x)
ld (hl), a
inc hl

ld a, (__en_y)
ld (hl), a
inc hl

ld a, (__en_x1)
ld (hl), a
inc hl

ld a, (__en_y1)
ld (hl), a
inc hl

ld a, (__en_x2)
ld (hl), a
inc hl

ld a, (__en_y2)
ld (hl), a
inc hl

ld a, (__en_mx)
ld (hl), a
inc hl

ld a, (__en_my)
ld (hl), a
inc hl

ld a, (__en_t)
ld (hl), a
inc hl
#endasm
# 539
}
# 544
}
# 7 "engine/hotspots.h"
void hotspots_init (void) {
gpit = 0; while (gpit < 6 * 5) {
hotspots [gpit].act = 1; ++ gpit;
}
}


void hotspots_do (void) {
if (hotspots [n_pant].act == 0) return;

cx2 = hotspot_x; cy2 = hotspot_y; if (collide ()) {

hotspot_destroy = 1;

switch (hotspots [n_pant].tipo) {

case 1:
# 34
++ p_objs;
# 39
;;
# 53
break;



case 2:
p_keys ++;
;;
break;



case 3:
p_life += 10;
if (p_life > 99)
p_life = 99;
;;

break;
# 101
}

if (hotspot_destroy) {
hotspots [n_pant].act = 0;
_x = hotspot_x >> 4; _y = hotspot_y >> 4; _t = orig_tile;
draw_invalidate_coloured_tile_g ();
hotspot_y = 240;
}
}
}
# 7 "mainloop.h"
void main (void) {
#asm




di

ld a, 195
ld (0x38), a
ld hl, _isr
ld (0x39), hl
jp isr_done

._isr
ei
ret

.isr_done
#endasm
#asm
# 30
ld a, 0x54
ld bc, 0x7F11
out (c), c
out (c), a
#endasm
#asm
# 39
ld hl, _trpixlutc
ld de, 0xF800 + 0x600
call depack
.vaudeville_tirants
#endasm


cortina ();

pal_set (my_inks);



cpc_SetMode (CPC_GFX_MODE);
#asm
# 57
; Horizontal chars (32), CRTC REG #1
ld b, 0xbc
ld c, 1 ; REG = 1
out (c), c
inc b
ld c, 32 ; VALUE = 32
out (c), c

; Horizontal pos (42), CRTC REG #2
ld b, 0xbc
ld c, 2 ; REG = 2
out (c), c
inc b
ld c, 42 ; VALUE = 42
out (c), c

; Vertical chars (24), CRTC REG #6
ld b, 0xbc
ld c, 6 ; REG = 6
out (c), c
inc b
ld c, 24 ; VALUE = 24
out (c), c
#endasm
# 86
sp_sw [0].cox = sm_cox [0];
sp_sw [0].coy = sm_coy [0];
sp_sw [0].invfunc = sm_invfunc [0];
sp_sw [0].updfunc = sm_updfunc [0];
sp_sw [0].sp0 = sp_sw [0].sp1 = (unsigned int) (sm_sprptr [0]);
# 109
for (gpit = 1 + 3 + 0; gpit < 1 + 3 + 0 + 3; gpit ++) {
sp_sw [gpit].cox = 0;
sp_sw [gpit].coy = 0;
sp_sw [gpit].invfunc =cpc_PutSpTileMap4x8;
sp_sw [gpit].updfunc = cpc_PutTrSp4x8TileMap2b;
sp_sw [gpit].sp0 = sp_sw [0].sp1 = (unsigned int) (sprite_19_a);
}



for (gpit = 0; gpit < 1 + 3 + 0 + 3; ++ gpit) {
spr_on [gpit] = 0;
sp_sw [gpit].ox = (1*8) >> 2;
sp_sw [gpit].oy = 2*8;
}
#asm
# 128
ei
#endasm


while (1) {
# 136
level = 0;
# 6 "my/title_screen.h"
{
blackout ();
#asm
# 14
ld hl, _s_title
ld de, 0x9000
call depack
#endasm



cpc_ShowTileMap (1);

select_joyfunc ();
}
# 164 "mainloop.h"
{
# 173
cortina ();
#asm
# 180
ld hl, _s_marco
ld de, 0x9000
call depack
#endasm


cpc_ShowTileMap (1);
# 6 "mainloop/game_loop.h"
playing = 1;
player_init ();


hotspots_init ();




locks_init ();
# 26
n_pant = 24;


maincounter = 0;
# 39
;;
# 55
p_killme = success = half_life = 0;

objs_old = keys_old = life_old = killed_old = 0xff;
# 84
o_pant = 0xff;
while (playing) {
p_kill_amt = 1;


if (o_pant != n_pant) {
# 91
draw_scr ();
o_pant = n_pant;
}
# 7 "./mainloop/hud.h"
if (p_objs != objs_old) {
draw_objs ();
objs_old = p_objs;
}



if (p_life != life_old) {
_x = 5; _y = 0; _t = p_life; print_number2 ();
life_old = p_life;
}



if (p_keys != keys_old) {
_x = 16; _y = 0; _t = p_keys; print_number2 ();
keys_old = p_keys;
}
# 156 "mainloop/game_loop.h"
maincounter ++;
half_life = !half_life;


player_move ();


enems_move ();



simple_coco_update ();


if (p_killme) {
player_kill (p_killme);
# 173
}
# 194
if (o_pant == n_pant) {
#asm
# 55 "./mainloop/update_sprites.h"
ld b, 0
._cpc_screen_update_inv_loop
push bc


ld a, b
sla a
sla a
sla a
sla a
ld d, 0
ld e, a
ld hl, _sp_sw
add hl, de


ld b, h
ld c, l


ld de, _cpc_screen_update_inv_ret
push de



ld de, 12
add hl, de
ld e, (hl)
inc hl
ld d, (hl)
push de


ld h, b
ld l, c




ret

._cpc_screen_update_inv_ret
pop bc
inc b
ld a, b
cp 1 + 3 + 0 + 3
jr nz, _cpc_screen_update_inv_loop

._cpc_screen_update_upd_buffer
call cpc_UpdScr
# 114
ld b, 1 + 3 + 0 + 3
._cpc_screen_update_upd_loop
dec b
push bc
ld a, b



sla a
sla a
sla a
sla a
ld d, 0
ld e, a
ld hl, _sp_sw
add hl, de


ld b, h
ld c, l


ld de, _cpc_screen_update_upd_ret
push de



ld de, 14
add hl, de
ld e, (hl)
inc hl
ld d, (hl)
push de


ld h, b
ld l, c




ret

._cpc_screen_update_upd_ret
pop bc
xor a
or b
jr nz, _cpc_screen_update_upd_loop

._cpc_screen_update_show
call cpc_ShowTouchedTiles
call cpc_ResetTouchedTiles
#endasm
# 196 "mainloop/game_loop.h"
}
# 208
hotspots_do ();
# 53 "./mainloop/flick_screen.h"
if (gpx == 0 && p_vx < 0) {
-- n_pant;
gpx = 224; p_x = 14336;
}
if (gpx == 224 && p_vx > 0) {
++ n_pant;
gpx = p_x = 0;
}
# 68
if (gpy == 0 && p_vy < 0 && n_pant >= 6) {
n_pant -= 6;

gpy = 144;
p_y = 9216;
}

if (gpy == 144 && p_vy > 0) {




if (n_pant < 6 * 5 - 6) {
n_pant += 6;

gpy = p_y = 0;
if (p_vy > 256) p_vy = 256;
}
# 98
}
# 273 "mainloop/game_loop.h"
if (0
# 278
|| p_objs == 25
# 287
) {
success = 1;
playing = 0;
}


if (p_life == 0
# 300
) {
playing = 0;
}
# 305
}

;;
# 223 "mainloop.h"
if (success) {
game_ending ();
} else {
game_over ();
}


cortina ();

}

clear_sprites ();
}
}
