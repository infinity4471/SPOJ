#include <cstdio>
#include <algorithm>
#include <cctype>

#define MAX 100000

using namespace std;

struct node {
	int flag,mod[3];
};

node *segtree;

#define updmod(i) \
	segtree[ i ].mod[ 0 ] = segtree[ 2*i ].mod[ 0 ] + segtree[ 2*i + 1].mod[ 0 ]; \
	segtree[ i ].mod[ 1 ] = segtree[ 2*i ].mod[ 1 ] + segtree[ 2*i + 1].mod[ 1 ]; \
	segtree[ i ].mod[ 2 ] = segtree[ 2*i ].mod[ 2 ] + segtree[ 2*i + 1].mod[ 2 ];
#define X10(n)	((n << 3) + (n << 1))
#define RI readint

const int MAXR = 65536;
char buf[MAXR], *lim = buf + MAXR - 1, *now = lim + 1;
bool adapt(){ // Returns true if there is a number waiting to be read, false otherwise
	while(now <= lim && !isdigit(*now)) ++now;
	if(now > lim){
		int r = fread(buf, 1, MAXR-1, stdin);
		buf[r] = 0;
		lim = buf + r - 1;
		if(r == MAXR - 1){
			while(isdigit(*lim)) ungetc(*lim--, stdin);
			if(*lim == '-') ungetc(*lim--, stdin);
		}
		now = buf;
	}
	while(now <= lim && !isdigit(*now)) ++now;
	return now <= lim;
}

bool readint(int& n){ // Returns true on success, false on failure
	if(!adapt()) return false;
	bool ngtv = *(now - 1) == '-';
	for(n = 0; isdigit(*now); n = X10(n) + *now++ - '0');
	if(ngtv) n = -n;
	return true;
}

void init(int i,int l,int r)
{
	if( l == r ) {
		segtree[ i ].mod[ 0 ] = 1;
		segtree[ i ].mod[ 1 ] = 0;
		segtree[ i ].mod[ 2 ] = 0;
	} else {
		init(2*i,l,(l + r) / 2);
		init(2*i+1,(l + r) / 2 + 1, r);
		updmod(i);
	}
	segtree[ i ].flag = 0;
}

inline void unflag(int i,int l,int r)
{
	int A[ 3 ];
	if( segtree[ i ].flag ) {
		A[ 0 ] = segtree[ i ].mod[ 0 ];
		A[ 1 ] = segtree[ i ].mod[ 1 ];
		A[ 2 ] = segtree[ i ].mod[ 2 ];
		for(int j = 0; j < 3; j++) {
			segtree[ i ].mod[ (j + segtree[ i ].flag) % 3 ] = A[ j ];
		}
		if( l != r ) {
			segtree[ 2*i ].flag += segtree[ i ].flag;
			segtree[ 2*i + 1].flag += segtree[ i ].flag;
		}
		segtree[ i ].flag = 0;
	}
}

int query(int n,int l,int r,int i,int j)
{
	if( r < i || l > j ) {
		return 0;
	}
	unflag( n,l,r );
	if( i <= l && r <= j ) {
		return segtree[ n ].mod[0];
	}
	else {
		return query(2*n,l,(l + r)/2,i,j) + query(2*n+1,(l + r)/2 + 1,r,i,j);
	}
}

void update(int n,int l,int r,int i,int j)
{
	if( r < i || l > j ) {
		unflag(n,l,r);
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag++;
		unflag(n,l,r);
	}
	else {
		unflag(n,l,r);
		update(2*n,l,(l + r) /2,i,j);
		update(2*n + 1,(l + r ) / 2 + 1, r,i,j);
		if( l!= r) {
			updmod(n);
		}
	}
}

int main( void )
{
	for(int n, m; RI(n) + RI(m) == 2 && (m || n); ){
		int b, e, op;
		segtree = new node[4*n+1];
		init(1, 1, n);
		for(int i = 0; i < m; ++i){
			RI(op), RI(b), RI(e);
			++b; ++e;
			if(op == 1){
				printf("%d\n",query(1,1,n,b,e));
			} else update(1, 1,n ,b, e);
		}
		puts("");
	}
	return 0;
}
