#include <cstdio>
#include <algorithm>
#include <ctime>

#define MAXN 100100
#define INF 1234567890

using namespace std;

struct node {
	int key, ans, subsize, prior;
	node* left, * right;
	node( int newkey ) {
		key = ans = newkey; subsize = 1; prior = rand() % INF + 1;
		left = right = NULL;
	}
};

int S( node* R )
{
	if( R != NULL ) return R->subsize;
	else return 0;
}

int A( node* R )
{
	if( R != NULL ) return R->ans;
	else return -INF;
}

void update( node* &R )
{
	if( R ) {
		R->subsize = 1 + S( R->left ) + S( R->right );
		R->ans = max( R->key, max( A( R->left ), A( R->right ) ) );
	}
}

void Lrotate( node* &R )
{
	node* temp = R->right;
	R->right = temp->left;
	temp->left = R;
	R = temp;
	update( R->left );
	update( R );
}

void Rrotate( node* &R )
{
	node* temp = R->left;
	R->left = temp->right;
	temp->right = R;
	R = temp;
	update( R->right );
	update( R );
}

void insert( node* &R, int pos, int newkey )
{
	if( R == NULL ) {
		R = new node( newkey );
		return;
	}
	if( S( R->left ) >= pos ) {
		insert( R->left, pos, newkey );
		if( R->prior > R->left->prior ) Rrotate( R );
	} else {
		insert( R->right, pos - S( R->left ) - 1, newkey );
		if( R->prior > R->right->prior ) Lrotate( R );
	}
	update( R );
}

int query( node* R, int l, int r, int i, int j )
{
	if( R == NULL || l >= j || r <= i ) return -INF;
	else if( i <= l && r <= j ) return A( R );
	else {
		int curkey = ( l + S( R->left ) >= i ) && ( l + S( R->left ) < j ) ? R->key: -INF;
		return max( curkey, max( query( R->left, l, l + S( R->left ), i, j ), query( R->right, l + S( R->left ) + 1, r, i, j ) ) );
	}
}

int main( void )
{
	node* root = NULL;
	srand( time( NULL ) );
	int N;
	scanf("%d", &N );
	while( N-- ) {
		char q[ 10 ];
		int u, v;
		scanf("%s%d%d", q, &u, &v );
		if( q[ 0 ] == 'A' ) insert( root, v - 1, u );
		else printf("%d\n", query( root, 0, root->subsize, u - 1, v ) );
	}
	return 0;
}
