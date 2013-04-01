//Tetris Game // This one is under development (ported from the shell) 
              // Just enjoy the one developed in shell to get the full features 
              // As which is pretty good!

//////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                          //
//   License: Boost Ver 1.0+                                                                //
//   Project: https://github.com/yongye/cpp                                                 //
//   Project: https://github.com/yongye/shell                                               //
//   Author : YongYe <complex.invoke@gmail.com>                                             //
//   Version: 1.0.0.9 02/20/2013 BeiJing China [Updated 04/01/2013]                         //
//                                                                                          //
//                                                                         [][][]           //
//   Algorithm:  [][][]                                                [][][][]             //
//               []                  [][][]                     [][][]     [][]             //
//   [][] [][]   []  [][][][]  [][][][][]    [][]             [][][]       []   [][] [][]   //
//   [] row []   []  [] (x-m)*zoomx  [][]    [] cos(a) -sin(a)  [][]       []   []  m  []   //
//   []     [] = []  []              []   *  []                 []         [] + []     []   //
//   [] col []   []  [] (y-n)*zoomy  []      [] sin(a)  cos(a)  []         []   []  n  []   //
//   [][] [][]   []  [][][][]  [][][][]      [][]             [][]         []   [][] [][]   //
//               []                                                        []               //
//               [][][]                                                [][][]               //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <tuple>
#include <atomic>
#include <vector>
#include <random>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <termios.h>
#include <initializer_list>
#include <boost/thread.hpp>
using namespace std;
using namespace boost;

const int box0[2] {4, 30};
const int box1[4] {4, 30, 4, 32};
const int box2[4] {4, 30, 5, 32};
const int box3[6] {4, 28, 4, 30, 4, 32};
const int box4[6] {4, 28, 4, 30, 5, 30};
const int box5[6] {4, 28, 5, 30, 6, 32};
const int box6[6] {4, 30, 5, 28, 5, 32};
const int box7[8] {4, 28, 5, 30, 6, 32, 7, 34};
const int box8[8] {4, 30, 5, 28, 5, 30, 5, 32};
const int box9[8] {4, 30, 5, 28, 5, 32, 6, 30};
const int box10[8] {4, 28, 4, 30, 4, 32, 4, 34};
const int box11[8] {4, 28, 5, 28, 5, 30, 5, 32};
const int box12[8] {4, 28, 4, 30, 5, 30, 5, 32};
const int box13[8] {4, 28, 4, 30, 5, 28, 5, 30};
const int box14[8] {4, 28, 4, 34, 5, 30, 5, 32};
const int box15[10] {4, 26, 4, 28, 4, 30, 4, 32, 4, 34};
const int box16[10] {4, 30, 5, 28, 5, 30, 5, 32, 6, 30};
const int box17[10] {4, 28, 4, 32, 5, 30, 6, 28, 6, 32};
const int box18[10] {4, 28, 4, 32, 5, 28, 5, 30, 5, 32};
const int box19[10] {4, 28, 4, 30, 5, 30, 6, 30, 6, 32};
const int box20[10] {4, 28, 5, 28, 6, 28, 6, 30, 6, 32};
const int box21[10] {4, 28, 4, 30, 5, 30, 5, 32, 6, 32};
const int box22[10] {4, 26, 4, 34, 5, 28, 5, 30, 5, 32};
const int box23[10] {4, 26, 4, 34, 5, 28, 5, 32, 6, 30};
const int box24[10] {4, 26, 5, 28, 6, 30, 7, 32, 8, 34};
const int box25[10] {4, 28, 4, 32, 5, 26, 5, 30, 5, 34};
const int box26[16] {4, 28, 4, 34, 5, 30, 5, 32, 6, 30, 6, 32, 7, 28, 7, 34};
const int box27[18] {4, 30, 5, 28, 5, 32, 6, 26, 6, 30, 6, 34, 7, 28, 7, 32, 8, 30};
const int box28[26] {4, 30, 5, 28, 5, 30, 5, 32, 6, 26, 6, 28, 6, 30, 6, 32, 6, 34, 7, 28, 7, 30, 7, 32, 8, 30};
const int box29[26] {4, 30, 5, 30, 6, 28, 6, 30, 6, 32, 7, 26, 7, 30, 7, 34, 8, 30, 9, 30, 10, 30, 11, 30, 12, 30};
const int box30[34] {4, 26, 4, 28, 4, 30, 4, 34, 5, 30, 5, 34, 6, 26, 6, 28, 6, 30, 6, 32, 6, 34, 7, 26, 7, 30, 8, 26, 8, 30, 8, 32, 8, 34};
const int box31[34] {4, 30, 5, 28, 6, 26, 6, 34, 7, 28, 7, 32, 7, 36, 8, 22, 8, 30, 8, 38, 9, 24, 9, 28, 9, 32, 10, 26, 10, 34, 11, 32, 12, 30};
const int length[32] {2, 4, 4, 6, 6, 6, 6, 8, 8, 8, 8, 8, 8, 8, 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 16, 18, 26, 26, 34, 34};
const int* BOX[32] {box0, box1, box2, box3, box4, box5, box6, box7, box8, box9, box10, box11, box12, box13, box14, box15, box16, box17, box18, 
                    box19, box20, box21, box22, box23, box24, box25, box26, box27, box28, box29, box30, box31};
const int toph=3;
const int modw=4;
random_device rnd;
atomic<int> sig(0);
int width=25;
int height=30;
int prelevel=6;
int runlevel=31;
int speedlevel=0;
int scorelevel=0;
int wthm=2*width+modw;
int dist=modw+wthm+3;
const string unit="[]";
int lower=height+toph;
vector<int> box, locus;
const string gmover="\e[?25h\e[36;26HGame Over!\e[0m\n";

static struct termios oldt;

void restore_terminal_settings()
{
   tcsetattr(0, TCSANOW, &oldt);
}

void disable_waiting_for_enter()
{
   struct termios newt;
   tcgetattr(0, &oldt); 
   newt=oldt;
   newt.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(0, TCSANOW, &newt);
   atexit(restore_terminal_settings);
}

void wait(int n)
{
   this_thread::sleep(boost::posix_time::milliseconds(n));
}

void runleave(int n)
{ 
   if ( n == 0 ) 
        cout<<gmover;
   else 
   {
      if (n == 1) sig=22;
      cout<<"\e[?25h\e[36;4H\n";
   }
}

struct data
{
   int value;
   data(): value(0){} 
};

int get_args(vector<string>& args)
{
   int args_len=args.size();
   if (args_len > 2)
   { 
       runlevel=stoi(args[1]);
       prelevel=stoi(args[2]);
       if (args_len > 3)
       {
          speedlevel=stoi(args[3]);
          if (args_len > 4)
          {
             width=stoi(args[4]);
             if (args_len > 5) height=stoi(args[5]);
          }
       }
       return 0;
   }
   else if (args_len == 2)
   {
       string str=args[1]; 
       if ( str == "-h" || str == "--help") 
       {
           cout<<"Usage: "<<args[0]<<" [runlevel] [previewlevel] [speedlevel] [width] [height]"<<endl;
           cout<<"Range: [ 0 =< runlevel <= 31 ]   [ previewlevel >= 1 ]   [ speedlevel <= 30 ]   [ width >= 17 ]   [ height>= 10 ]"<<endl;
           return 1;
       }
       else if ( str == "-v" || str == "--version" )
       {
           cout<<"Tetris Game  Version 1.0.0.9 [Updated 04/01/2013]"<<endl;
           return 1;
       }
       else
       {
           runlevel=stoi(args[1]);   
           return 0;
       }
   }
   return 0;
}

class piece;

class board
{
   public:
      board(){}
      void border();
      void notify();
      void matrix();
};

class transpose
{
   public:
      transpose(){}
      friend class piece;
      vector<int> unique(vector<int>&);
      void addbox(vector<int>&, int, int);
      tuple<int, int> mid_point(vector<int>&);
      vector<int> multiple(vector<int>&, int, int);
      void coordinate_transformation(double, int, int);
      void abstract(vector<int>&, int&, int&, int, int);
      void optimize(vector<int>&, initializer_list<int>);
   protected:
      vector<int> new_box, new_coordinate;
};

class get_time
{
   public:
      void current();
      void resize(initializer_list<int> dhms);
      void set_time(int&, int&, int value=60); 
   protected:
      int day=0;
      int hour=0;
      int minute=0;
      int second=0;
      map<int, string> time;
      string color="\e[1;33m";
      string line="";
};

class piece
{
   public:
      piece();
      int persig();
      int getsig();
      void drawbox();
      void get_erase();
      void clear_row();
      int drop_bottom();
      void init_color();
      void ghost_cross();
      void init(int, int);
      void random_piece();
      void check(int, int);
      void get_invoke(int);
      void show_piece(int);
      void shift_piece(int);
      void update(int, int);
      void perplus(int, int);
      vector<int>& get_piece();
      void move(double&, int&);
      void rotate(double&, int&);
      int move_piece(double, int);
      void coordinate(vector<int>&);
      void transform(double, int dy=1);
      string& get_replace(string& str);
      void draw_piece(int, double, int);
      void top_point(vector<int>& cur_box);
      void runbomb(int x, int y, int size);
      void coord_comp(int&, int&, int&, int&);
      void get_point(vector<int>&, int&, int&, int);
      void get_preview(vector<int>&, string&, int, string&);
      void loop(void (piece::*lhs)(int, int), void (piece::*rhs)(int)=nullptr);
      void pipe_piece(vector<int>&, vector<int>&, string&, int, int, string&, string&);
   protected:
      board bd;
      int line=0;
      int count=0;
      bool full=true;
      transpose trans;
      vector<int> preview_box;
      vector<vector<string>> box_color;
      vector<vector<int>> box_map, next_preview_piece;
      vector<string> old_preview_block, next_preview_color, color;
      string cur_shadow, cur_color, old_shadow, cur_preview_block;
};

int main(int argc, char* argv[])
{
   vector<string> args(argv, argv+argc);
   if (get_args(args)) exit(0) ;
   piece pg;
   get_time time;
   thread t0{&get_time::current, &time};
   thread t1{&piece::persig, &pg};
   pg.getsig();
}

vector<int> transpose::unique(vector<int>& new_coordinate)
{
   map<string, int> mid;
   vector<int> first_coordinate;
   for (int i=0; i!=new_coordinate.size(); i+=2)
   {
        string key=to_string(new_coordinate[i])+"::"+to_string(new_coordinate[i+1]);
        if ( !mid[key]++ ) 
        {
             first_coordinate.push_back(new_coordinate[i]);
             first_coordinate.push_back(new_coordinate[i+1]);
        }
   }
   return first_coordinate;
}

void transpose::addbox(vector<int>& new_box, int k, int j)
{
   for(int i=0; i!=new_box.size(); i+=2)
   {
       new_box[i+k]+=j;
   }
}

tuple<int, int> transpose::mid_point(vector<int>& mid)
{
   if ( mid.size()%4 ) 
   {
        return make_tuple(mid[mid.size()/2-1], mid[mid.size()/2]);
   }
   else
   {
        return make_tuple(mid[mid.size()/2], mid[mid.size()/2+1]);
   }
}

vector<int> transpose::multiple(vector<int>& dim, int b, int d)
{
   vector<int> mid(dim);
   for (int i=0; i!=mid.size()-2; i+=2)
   {
        mid[i+3]=mid[i+1]+(dim[i+3]-dim[i+1])*b/d;
   }
   return mid;
}

void transpose::coordinate_transformation(double dx, int m, int n)
{
   int len=new_box.size();
   new_coordinate.assign(len,0);           
   for (int i=0; i!=len; i+=2)                             // row=(x-m)*zoomx*cos(a)-(y-n)*zoomy*sin(a)+m
   {                                                       // col=(x-m)*zoomx*sin(a)+(y-n)*zoomy*cos(a)+n
        new_coordinate[i]=m+new_box[i+1]-n;                // a=-pi/2 zoomx=+1 zoomy=+1 dx=0 dy=0
        new_coordinate[i+1]=(new_box[i]-m)*dx+n;           // a=-pi/2 zoomx=-1 zoomy=+1 dx=0 dy=0 
   }                                                       // a=+pi/2 zoomx=+1 zoomy=-1 dx=0 dy=0
   if ( dx == 0.5 ) new_coordinate=unique(new_coordinate);
}

void transpose::abstract(vector<int>& pix, int& i, int& j, int b, int d)
{
   new_box=multiple(pix, b, d);
   tie(i, j)=mid_point(new_box);
}

void transpose::optimize(vector<int>& new_box, initializer_list<int> ink)
{
   int n=0;
   for (auto& j : ink)
   {
       ++n;
       if ( j )
       {
            int k=n>1?1:0;
            addbox(new_box, k, j);
       } 
   }
}

void get_time::set_time(int& lhs, int& rhs, int value)
{
   if (lhs == value )
   {
      ++rhs;
      lhs=0;
   }
   time[lhs]=to_string(lhs);
}

void get_time::resize(initializer_list<int> dhms)
{
   for (auto& p : dhms)
   {
        string s=to_string(p);
        time[p]=s;
     if (s.size() != 2) time[p]="0"+s;
   }
}

void get_time::current()
{
   int j=width-9;
   for(int k=0; k!=j; ++k) line+='-';
   cout<<"\e[2;6H"+color+line+"[\e[2;"+to_string(23+j)+"H"+color+"]"+line+"\e[0m\n";
   while (true)
   {
       if ( sig == 22 ) { runleave(0); break; }
       thread time_thread(wait, 1000);
       time.clear();
       set_time(second, minute);
       set_time(minute, hour);
       set_time(hour, day, 24);
       time[day]=day;
       resize({day, hour, minute, second});
       cout<<"\e[2;"+to_string(7+j)+"H"+color+"Time "+time[day]+":"+time[hour]+":"+time[minute]+":"+time[second]+"\e[0m\n";
       time_thread.join();
       ++second;
   }
} 

piece::piece()
{
   prelevel=(prelevel < 1)?6:prelevel;            
   speedlevel=(speedlevel > 8)?0:speedlevel;
   runlevel=(runlevel < 0 || runlevel > 31)?32:runlevel+1;            
   width=width<17?25:width;
   height=height<10?30:height;
   lower=height+toph;
   wthm=2*width+modw;
   dist=modw+wthm+3;
   vector<int> v;
   vector<string> u;
   box_map.assign(height, v);
   box_color.assign(height, u);
   for (int i=0; i!=height; ++i)
   {
       box_map[i].assign(width, 0);
       box_color[i].assign(width, "");
   }
   old_preview_block.assign(prelevel,"");
   next_preview_color.assign(prelevel,"");
   for (int i=0; i!=prelevel; ++i) 
        next_preview_piece.push_back(v);
   printf("%c%c%c%c%c%c",27,'[','H',27,'[','J' );
   loop(&piece::init);
   init_color();
   bd.border();
   bd.matrix();
   bd.notify();
   show_piece(1);
   draw_piece(1,0,0);
}

void piece::check(int i, int j)
{ 
   if ( ! box_map[i-modw][j/2-toph] ) full=false; 
}

void piece::update(int i, int j)
{ 
   string pos="\e["+to_string(i)+";"+to_string(j)+"H";
   if ( ! box_map[i-modw][j/2-toph] ) 
        cout<<pos+"  ";
   else
        cout<<pos+"\e["+box_color[i-modw][j/2-toph]+unit+"\e[0m";
}

int piece::drop_bottom()
{
   map<int, data>            col;
   map<int, pair<int, int>>  row;
   for (int i=0; i!=box.size(); i+=2)
   {   
        int q=box[i];
        int p=box[i+1];
        int& value=col[p].value;
        if ( value == 0 ) value=box[i];
        if ( value < q ) value=q;
        row[p]=make_pair(value, p);
   }
   vector<int> max;
   for (auto& key : row)
   {
        auto p=key.second;
        max.push_back(p.first);
        max.push_back(p.second);
   }
   
   for (int i=0, j=0; i!=height; j+=2)
   { 
        if (box_map[max[j]+i-modw][max[j+1]/2-toph] == 1) return i-1;
        if (max[j]+i == lower) return i;
        if (j+2 == max.size())
        { 
            j=-2; 
            ++i;
        }
   }
}     

vector<int>& piece::get_piece()
{
   box.clear();
   int len=rnd()%runlevel;
   copy(BOX[len], BOX[len]+length[len], back_inserter(box));
   return box;
}

void piece::init(int i, int j)
{ 
   box_map[i-modw][j/2-toph]=0;
   box_color[i-modw][j/2-toph]=""; 
}

void piece::init_color()
{
   for (int i=0; i!=9; ++i)
   {
     for (int j=0; j!=9; ++j)
     {
       string s="1;3"+to_string(i)+";4"+to_string(j)+"m";
       color.push_back(s);
     }
   }
   
   for (int i=0, j=38; i!=2; ++i, j+=10)
   {
     for (int k=0; k!=256; ++k)
     {
       string s=to_string(j)+";5;"+to_string(k)+";1m";
       color.push_back(s);
     }
   }
}

void piece::loop(void (piece::*lhs)(int, int), void (piece::*rhs)(int))
{
   for(int i=4,j=6,l=wthm; i<=lower; j+=2)
   {
       full=true; 
       (this->*lhs)(i, j);
       if ( ! full || j == l )
       {
            if ( full && rhs) (this->*rhs)(i);
            j=4; 
            ++i;
       }
   }
}

string& piece::get_replace(string& src)
{ 
   size_t pos = 0;
   while((pos = src.find(unit, pos)) != string::npos) 
   {
       src.replace(pos, unit.size(), "  ");
       pos+=unit.size(); 
   }
   return src;
}

void piece::shift_piece(int i)
{
   ++line;
   for(int j=i; j>toph+1; --j)
   {
       box_color[j-modw]=box_color[j-5];
       box_map[j-modw]=box_map[j-5]; 
   }
   box_map[0].assign(width, 0);
   box_color[0].assign(width, "");
}

void piece::get_preview(vector<int>& box0, string& old_block, int n, string& new_block_color)
{
   for(int i=0; i!=box0.size(); i+=2)
   {
        int col=box0[i+1]-(n-dist);
        cur_preview_block+="\e["+to_string(box0[i]-1)+";"+to_string(col)+"H"+unit;
   }
   cout<<get_replace(old_block)+"\e["+new_block_color+cur_preview_block+"\e[0m\n";
}

void piece::get_erase()
{  
   cout<<get_replace(old_shadow)+"\e[0m\n"; 
}

void piece::pipe_piece(vector<int>& next_preview_box0, vector<int>& next_preview_box1, 
string& old_preview_box, int n, int p, string& new_preview_color0, string& new_preview_color1)
{
   next_preview_box0.clear();
   cur_preview_block="";
   if (p) 
   {
      next_preview_box0=get_piece();
      cur_color=color[rnd()%color.size()];
      new_preview_color0=cur_color;
      get_preview(box, old_preview_box, n, cur_color);
   }
   else 
   {
      next_preview_box0=next_preview_box1;
      new_preview_color0=new_preview_color1;
      get_preview(next_preview_box1, old_preview_box, n, new_preview_color1);
   }
   old_preview_box=cur_preview_block;
}

void piece::get_invoke(int n)
{
   for(int i=0; i!=prelevel-1; ++i)
   {
       pipe_piece(next_preview_piece[i], next_preview_piece[i+1], old_preview_block[i], 12*(2-i), n, next_preview_color[i], next_preview_color[i+1]);
   }
}
            
void piece::show_piece(int n)
{
   int end=prelevel-1;
   cur_color=next_preview_color[0];
   preview_box=next_preview_piece[0];
   get_invoke(n);
   cur_preview_block="";
   next_preview_piece[end]=get_piece();
   next_preview_color[end]=color[rnd()%color.size()];
   get_preview(box, old_preview_block[end], 12*(2-end), next_preview_color[end]);
   old_preview_block[end]=cur_preview_block;
   box=preview_box;
}

void piece::coordinate(vector<int>& lbox)
{
   cur_shadow="";
   locus=lbox;
   for(int i=0; i!=locus.size(); i+=2)
   {    
        cur_shadow+="\e["+to_string(locus[i])+";"+to_string(locus[i+1])+"H"+unit;
   }
}

void piece::draw_piece(int n, double dx, int dy)
{
   if (n)
   {
      cur_color=color[rnd()%color.size()];
      coordinate(get_piece());
   }
   else
   {
      cur_color=next_preview_color[0];
      coordinate(next_preview_piece[0]);
   }
   drawbox();
   if (! move_piece(dx, dy)) { sig=22; runleave(0); }
}

void piece::random_piece()
{
   ++count;
   int k=height-1;
   for (int i=0,j=6; i!=count; j+=2)
   {
        if ( j == wthm ) { j=4; ++i; }
        if ( rnd()%2 ) 
        { 
            box_map[k-i][j/2-toph]=1; 
            box_color[k-i][j/2-toph]=color[rnd()%color.size()];
        }
   }
   if ( count == k ) count=0;
}

void piece::coord_comp(int&x, int& y, int& u, int& v)
{
   if ( x <= y )
   { 
       x=y;
       if ( u < v ) u=v;
   }
}

void piece::top_point(vector<int>& cur_box)
{
   int x, y; 
   int u=cur_box[0];
   int v=cur_box[1];
   for (int i=0; i!=cur_box.size(); i+=2)
   {
        coord_comp(x, cur_box[i], y, cur_box[i+1]);
        coord_comp(cur_box[i], u, cur_box[i+1], v);
   }
   if ( x-u == 3 && y-v == 6 )
   {
         cur_box.clear();
         initializer_list<int> radius={x-3, y-6, x-3, y, x, y-6, x, y};
         for (auto& il : radius)
             cur_box.push_back(il);
   }
}

void piece::runbomb(int x, int y, int size)
{
   string empty;
   vector<int> radius={x-1, y-2, x-1, y, x-1, y+2, x, y-2, x, y, x, y+2, x+1, y-2, x+1, y, x+1, y+2};
   for(int j=0; j!=radius.size(); j+=2)
   {
        int p=radius[j];
        int q=radius[j+1];
        bool boolp=(p > toph && p <= lower);
        bool boolq=(q <= wthm && q > modw);
        if ( boolp && boolq )
        {
             if ( ! box_map[p-modw][q/2-toph] && p+q != x+y && size != 8 ) continue;
              empty+="\e["+to_string(p)+";"+to_string(q)+"H"+"\040\040";
              init(p, q); 
        }
   }
   wait(0);
   cout<<empty<<endl;
} 

void piece::clear_row()
{
   vector<int> cur_box(locus);
   int len=cur_box.size();
   if ( len == 16 ) top_point(cur_box);
   for (int i=0; i!=cur_box.size(); i+=2)
   {
        int x=cur_box[i];
        int y=cur_box[i+1];
        if ( len == 16 )
        {
             runbomb(x, y, cur_box.size());
        }
        else
        {
            box_map[x-modw][y/2-toph]=1;
            box_color[x-modw][y/2-toph]=cur_color;
        }
   }
   line=0;
   loop(&piece::check, &piece::shift_piece);
   if ( ! line ) return;
   int num=line*200-100;
   cout<<"\e[1;34m\e["+to_string(toph+10)+";"+to_string(dist+49)+"H"+to_string(scorelevel+=num)+"\e[0m\n";
   if ( scorelevel%5000 < num && speedlevel < 8 )
   {
         random_piece();
         cout<<"\e[1;34m\e["+to_string(toph+10)+";"+to_string(dist+30)+"H"+to_string(++speedlevel)+"\e[0m\n";
   }
   loop(&piece::update);
}        

int piece::persig()
{
   int j=0;
   while ( ++j )
   {
         if ( j != 1 ) wait(0);
         int sigswap=sig;
         sig=0;
         switch (sigswap)
         {
            case 22 : runleave(0     );           return 0;
            case 23 : transform(-1   );           break;
            case 24 : transform(1    );           break;
            case 25 : transform(-2   );           break;
            case 26 : transform(0.5  );           break;
            case 27 : transform(0, -2);           break;
            case 28 : transform(0,  2);           break;
            case 29 : transform(1,  0);           break;
            case 30 : transform(-1, 0);           break;
            case 31 : transform(drop_bottom(),0); break;
         }
         if ( j == 9-speedlevel ) { transform(1,0); j=0; }
   }
   return 0;
}

int piece::getsig()
{
   cout<<"\e[?25l";
   disable_waiting_for_enter();
   char key;
   char pool='\e'; 
   char arry[3]="";
   while (true)
   {
       key=getchar();
       sig=0;
       arry[0]=arry[1]; 
       arry[1]=arry[2];
       arry[2]=key;
       if   ( key == ' ' || key == '\n' ) sig=31;
       else if ( key == pool && arry[1] == pool ) { runleave(1); return 0; }
       else if ( arry[0] == pool && arry[1] == '[' )
       {
            switch (key)
            {
               case 'A':  sig=23; break;
               case 'B':  sig=29; break;
               case 'D':  sig=27; break;
               case 'C':  sig=28; break;
            }
                 
       }
       else
       {
            switch (key)
            {
               case 'W': 
               case 'w': sig=23; break;
               case 'T':
               case 't': sig=24; break;
               case 'M':
               case 'm': sig=25; break;
               case 'N':
               case 'n': sig=26; break;
               case 'S':
               case 's': sig=29; break;
               case 'A':
               case 'a': sig=27; break;
               case 'D':
               case 'd': sig=28; break;
               case 'U':
               case 'u': sig=30; break;
               case 'P':
               case 'p': sig=19; break;
               case 'R':
               case 'r': sig=18; break;
               case 'Q':
               case 'q': runleave(1); return 0;
            }
       }
       if ( sig == 22 ) { runleave(1); return 0;}
   }
   return 0;
}


void piece::drawbox()
{ 
   old_shadow=cur_shadow; 
   cout<<"\e["+cur_color+cur_shadow+"\e[0m\n"; 
}

int piece::move_piece(double dx, int dy)
{
   int len=locus.size();
   for (int i=0; i!=len; i+=2)
   { 
        int x=locus[i]+dx;
        int y=locus[i+1]+dy;
        bool boolx=(x <= toph || x > lower);
        bool booly=(y >= wthm+2 || y <= modw+1);
        if ( boolx || booly ) return 0;
        if ( box_map[x-modw][y/2-toph] )
        {
             if ( len == 2 )
             {
                    for (int j=lower; j>x; --j)
                    {
                         if ( ! box_map[j-modw][y/2-toph] ) return 1;
                    }
             }
             return 0;
        }
   }
   return 1;  
}

void piece::ghost_cross()
{
   int i=locus[0];
   int j=locus[1];
   if ( box_map[i-modw][j/2-toph] ) cout<<"\e["+to_string(i)+";"+to_string(j)+"H\e["+box_color[i-modw][j/2-toph]+unit+"\e[0m\n";
}

void piece::perplus(int dx, int dy)
{
   if ( locus.size() == 2 )  ghost_cross();
   vector<int> new_box(box);
   trans.optimize(new_box, {dx, dy});
   coordinate(new_box);
   box=new_box;
}

void piece::move(double& dx, int& dy)
{
   if (move_piece(dx, dy))
   {
        get_erase();
        perplus(dx, dy);
        drawbox();
   }
   else
   {
        if ( dx == 1 )
        {
            clear_row();  
            draw_piece(0,dx, dy); 
            show_piece(0);
        }
   } 
}

void piece::rotate(double& dx, int& dy)
{     
   int m,n,p,q,mp,nq;
   tie(mp,nq)=trans.mid_point(box); 
   trans.abstract(box, m, n, 1, 2);
   trans.coordinate_transformation(dx, m, n); 
   dx=dy=0;
   trans.abstract(trans.new_coordinate, p, q, 2, 1);
   trans.optimize(trans.new_box, {mp-p, nq-q});
   locus=trans.new_box;
   if (move_piece(dx, dy))
   {
       get_erase(); 
       coordinate(trans.new_box);
       drawbox(); 
       box=locus;
   }
   else
   {
       locus=box;
   }
}

void piece::transform(double dx, int dy)
{ 
   if ( dy != 1 )
        move(dx, dy);
   else
        rotate(dx, dy); 
}

void board::border()
{
   string boucol="\e[38;5";
   int num=rnd()%145+6;
   for (int i=6; i<=wthm; i+=2)
   {
        string str1=boucol+";"+to_string(num+i)+";1m\e["+to_string(toph)+";"+to_string(i)+"H==";
        string str2=boucol+";"+to_string(num+i+25)+";1m\e["+to_string(lower+1)+";"+to_string(i)+"H==\e[0m";
        cout<<str1+str2<<endl;
   }
   for (int i=toph; i<=lower+1; ++i)
   {
        string str1=boucol+";"+to_string(num+i)+";1m\e["+to_string(i)+";"+to_string(modw)+"H||";
        string str2=boucol+";"+to_string(num+i+30)+";1m\e["+to_string(i)+";"+to_string(wthm+2)+"H||\e[0m";
        cout<<str1+str2<<endl;
   }
}

void board::notify()
{
   string str0="\e[1;34m\e["+to_string(toph+10)+";"+to_string(dist+49)+"H"+to_string(scorelevel);
   string str1="\e[1;34m\e["+to_string(toph+10)+";"+to_string(dist+30)+"H"+to_string(speedlevel)+"\e[0m";
   cout<<str0+str1<<endl;
   string str2="\e[1;34m\e["+to_string(toph+10)+";"+to_string(dist)+"H"+to_string(runlevel-1);
   string str3="\e[1;34m\e["+to_string(toph+10)+";"+to_string(dist+15)+"H"+to_string(prelevel)+"\e[0m";
   cout<<str2+str3<<endl;
   string str4="\e[1;31m\e["+to_string(toph+9)+";"+to_string(dist)+"HRunLevel\e[1;31m\e[";
   string str5=to_string(toph+9)+";"+to_string(dist+15)+"HPreviewLevel\e[0m";
   cout<<str4+str5<<endl;
   string str6="\e[1;31m\e["+to_string(toph+9)+";"+to_string(dist+30)+"HSpeedLevel\e[1;31m\e[";
   string str7=to_string(toph+9)+";"+to_string(dist+49)+"HScoreLevel\e[0m";
   cout<<str6+str7<<endl;
   cout<<"\e[38;5;34;1m\e["+to_string(toph+12)+";"+to_string(dist)+"HM|m      ===   double         N|n          ===   half\n";
   cout<<"\e["+to_string(toph+13)+";"+to_string(dist)+"HQ|q|ESC  ===   exit           U|u          ===   one step up\n";
   cout<<"\e["+to_string(toph+14)+";"+to_string(dist)+"HP|p      ===   pause          S|s|down     ===   one step down\n";
   cout<<"\e["+to_string(toph+15)+";"+to_string(dist)+"HR|r      ===   resume         A|a|left     ===   one step left\n";
   cout<<"\e["+to_string(toph+16)+";"+to_string(dist)+"HW|w|up   ===   rotate         D|d|right    ===   one step right\n";
   cout<<"\e["+to_string(toph+17)+";"+to_string(dist)+"HT|t      ===   transpose      Space|enter  ===   drop all down\n";
   cout<<"\e[38;5;106;1m\e["+to_string(toph+19)+";"+to_string(dist)+"HTetris Game  Version 1.0.0.9\n";
   string str8="\e["+to_string(toph+20)+";"+to_string(dist)+"HYongYe <complex.invoke@gmail.com>\e[";
   string str9=to_string(toph+21)+";"+to_string(dist)+"H02/20/2013 BeiJing China [Updated 04/01/2013]";
   cout<<str8+str9<<endl;
}

void board::matrix()
{
   string one=" ";
   string sr="\e[0m";
   string trx="[][]";
   string two=one+one;
   string tre=one+two;
   string cps=two+tre;
   string spc=cps+cps;         
   string equ="\e[38;5;191;1m";
   string colbon="\e[38;5;47;1m";
   string mcol="\e[38;5;30;1m";
   string fk5=spc+spc;
   string fk4=mcol+"[]"+sr;
   string fk0=colbon+"[]"+sr;
   string fk1=colbon+trx+sr;
   string fk6=mcol+"[]"+trx+sr;
   string fk2=colbon+"[]"+trx+sr;
   string fk3=colbon+trx+trx+sr;
   string fk=tre+fk0+two+fk3+two+fk3;
   string fk7=fk1+one+fk1+fk+fk4+two+two;
   string fk8=fk0+one+equ+"row"+one+fk0+tre+fk0+two+fk0+one+equ+"(x-m)*zoomx"+two;
   string fk9=one+equ+"="+one+fk0+two+fk0+spc+tre+one+fk0+tre+equ+"*"+two;
   string fk10=spc+cps+two+fk0+two+fk0+one+equ+"+"+one+fk0+cps+fk0;
   string fk11=tre+one+fk0+two+equ+"cos(a)"+one+equ+"sin(a)"+two+fk0+two+fk0+tre+fk0+two+equ+"m"+two+fk0;
   string fk12=one+equ+"col"+one+fk0+tre+fk0+two+fk0+one+equ+"(y-n)*zoomy"+two+fk0+cps+one;
   string fk13=one+equ+"-sin(a)"+one+equ+"cos(a)"+two+fk0+two+fk0+tre+fk0+two+equ+"n"+two+fk0;
   string fk14=fk1+one+fk1+fk+cps+one;
   string fk15=fk1+two+fk0+tre+fk1+one+fk1;
   cout<<"\e["+to_string(toph+23)+";"+to_string(dist)+"H"+colbon+"Algorithm:"+two+fk2+one+fk5+fk5+fk2+fk4<<endl;
   cout<<"\e["+to_string(toph+30)+";"+to_string(dist)+"H"+spc+two+fk0+two+two+cps+fk5+fk5+fk0<<endl;
   cout<<"\e["+to_string(toph+25)+";"+to_string(dist)+"H"+fk7+fk1+spc+tre+fk1+two+fk0+tre+fk1+one+fk1<<endl;
   cout<<"\e["+to_string(toph+26)+";"+to_string(dist)+"H"+fk8+fk0+fk4+fk11+"\e["+to_string(toph+28)+";"+to_string(dist)+"H"+fk0+fk12+fk0+fk13<<endl;
   cout<<"\e["+to_string(toph+24)+";"+to_string(dist)+"H"+two+spc+fk0+spc+tre+two+tre+fk6+fk5+cps+fk0+fk4<<endl;
   string str0="\e["+to_string(toph+22)+";"+to_string(dist)+"H"+tre+fk5+fk5+fk5+fk6+"\e[";
   string str1=to_string(toph+29)+";"+to_string(dist)+"H"+fk14+fk1+spc+tre+fk15;
   cout<<str0+str1<<endl;
   string str2="\e["+to_string(toph+27)+";"+to_string(dist)+"H"+fk0+cps+fk0+fk9+fk0+fk10;
   string str3="\e["+to_string(toph+31)+";"+to_string(dist)+"H"+spc+two+fk2+fk5+fk5+" "+fk2;
   cout<<str2+str3<<endl;
}
