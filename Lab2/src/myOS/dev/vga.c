/*
 * 本文件实现vga的相关功能，清屏和屏幕输出
 * clear_screen和append2screen必须按照如下借口实现
 * 可以增加其他函数供clear_screen和append2screen调用
 */
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA 0x3D5

extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);
//VGA字符界面规格：25行80列
//VGA显存初始地址为0xB8000

short cur_line=0;
short cur_column=0;//当前光标位置
char * vga_init_p=(char *)0xB8000;

/*

*不必局限于以下框架，可以自定义接口来实现，只需要保证append2screen接口能够
被正确调用即可  

*/
void update_cursor(void){//通过当前行值cur_cline与列值cur_column回写光标
	//TODO:填写正确的内容
	int cur_position = cur_line * VGA_WIDTH + cur_column;

	outb(VGA_CRTC_INDEX, 0x0E);
	outb(VGA_CRTC_DATA, (cur_position >> 8) & 0xFF);

	outb(VGA_CRTC_INDEX, 0x0F);
	outb(VGA_CRTC_DATA, cur_position & 0xFF);
}

short get_cursor_position(void){//获得当前光标，计算出cur_line和cur_column的值
	//TODO:填写正确的内容
	int cur_position = 0;

	outb(VGA_CRTC_INDEX, 0x0E);
	cur_position |= (inb(VGA_CRTC_DATA) << 8);

	outb(VGA_CRTC_INDEX, 0x0F);
	cur_position |= inb(VGA_CRTC_DATA);

	cur_line = cur_position / VGA_WIDTH;
	cur_column = cur_position % VGA_WIDTH;

	return cur_position;
}


void clear_screen(void) {//清屏
	//TODO:填写正确的内容 
	for (int i=0; i < VGA_WIDTH * VGA_HEIGHT; i++){
		vga_init_p[i * 2] = ' ';
		vga_init_p[i * 2 + 1] = 0x07;
	}   

	cur_line=0;
	cur_column=0;
	update_cursor();
}

void append2screen(char *str,int color){ //将str输出到vga屏幕
	//TODO:填写正确的内容    
	while(*str){
		if(*str == '\n') {
			cur_line++;
			cur_column=0;
		}
		else{
			int offset = (cur_line * VGA_WIDTH + cur_column)*2;
			vga_init_p[offset] = *str;
			vga_init_p[offset + 1] = color;
			cur_column++;
		}

		if(cur_column >= VGA_WIDTH){
			cur_line++;
			cur_column = 0;
		}

		if(cur_line >= VGA_HEIGHT){
			for(int i = 0; i < VGA_HEIGHT; i++){
				for(int j = 0; j < VGA_WIDTH; j++){
					int src_offset = (i * VGA_WIDTH + j) * 2;
					int dst_offset = ((i - 1) * VGA_WIDTH + j) * 2;
					vga_init_p[dst_offset] = vga_init_p[src_offset];
					vga_init_p[dst_offset + 1] = vga_init_p[src_offset + 1];
				}
			}

			for(int j = 0; j < VGA_WIDTH; j++){
				int offset = ((VGA_HEIGHT - 1) * VGA_WIDTH + j) * 2;
				vga_init_p[offset] = ' ';
				vga_init_p[offset + 1] = 0x07;
			}

			cur_line = VGA_HEIGHT - 1;
		}
		str++;
	}
	update_cursor();
}


