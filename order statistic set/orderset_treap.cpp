#include <cstdio>
#include <algorithm>
#include <ctime>

#define INF 100000000
#define MAXN 201000

using namespace std;

struct node {
	int priority, key, size;
	struct node* left;
	struct node* right;
	node(int newkey) {
		priority = rand() % INF + 1;
		key = newkey;
		size = 1;
		left = right = NULL;
	}
};

int S( node* root )
{
	if( root == NULL ) {
		return 0;
	} else {
		return root->size;
	}
}

void update_size( node* &root )
{
	if( root ) {
		root->size = S( root->left ) + S( root->right ) + 1;
	}
}

void left_rotate( node* &r )
{
	node* temp = r->right;
	r->right = temp->left;
	temp->left = r;
	r = temp;
	update_size( r->left );
	update_size( r );
}

void right_rotate( node* &r )
{
	node* temp = r->left;
	r->left = temp->right;
	temp->right = r;
	r = temp;
	update_size( r->right );
	update_size( r );
}

void insert( int newkey, node* &root )
{
	if( root == NULL ) {
		root = new node( newkey );
		return;
	}
	if( newkey < root->key ) {
		insert( newkey, root->left );
		if( root->priority > root->left->priority ) {
			right_rotate( root );
		}
	}
	else if( newkey > root->key ) {
		insert( newkey, root->right );
		if( root->priority > root->right->priority ) {
			left_rotate( root );
		}
	}
	update_size( root );
}

int kth( int k, node* root )
{
	if( root == NULL ) {
		return -1;
	}
	int val = S( root->left ) + 1;
	if( val == k ) {
		return root->key;
	}
	else if( k < val ) {
		return kth( k, root->left );
	} return kth( k - val, root->right );
}

int count( int newkey, node* root )
{
	if( root == NULL ) {
		return 0;
	}
	if( newkey <= root->key ) {
		return count( newkey, root->left );
	} else {
		return count( newkey, root->right ) + S( root->left ) + 1;
	}
}

void erase( int newkey, node* &root )
{
	if( root == NULL ) {
		return;
	}
	if( newkey < root->key ) {
		erase( newkey, root->left );
	}
	else if( newkey > root->key ) {
		erase( newkey, root->right );
	} else {
		if( root->left && root->right ) {
			if( root->left->priority < root->right->priority ) {
				right_rotate( root );
			} else {
				left_rotate( root );
			}
				erase( newkey, root );
		} else {
			node* temp = root;
			if( root->left ) {
				root = root->left;
			} else {
				root = root->right;
			}
			delete temp;
		}
	}
	update_size( root );
}

bool find( int newkey, node* root )
{
	if( root == NULL ) {
		return 0;
	}
	else if( root->key == newkey ) {
		return true;
	}
	if( newkey <= root->key ) {
		return find( newkey, root->left );
	} return find( newkey, root->right );
}

int main( void )
{
	int Q;
	scanf("%d", &Q );
	node* root = NULL;
	srand( time( NULL ) );
	while( Q-- ) {
		char q;  
        	int num;  
       		scanf("%*c%c%d", &q,&num);
		if( q == 'I' ) {
			if( !find( num, root ) ) {
				insert( num, root );
			}
		}
		else if( q == 'K' ) {
			int kk = kth( num, root );
			if( kk == -1 ) {
				printf("invalid\n");
				continue;
			}
			printf("%d\n", kk );
		}
		else if( q == 'C' ) {
			printf("%d\n", count( num, root ) );
		}
		else if( q == 'D' ) {
			if( find( num, root ) ) {
				erase( num, root );
			}
		}
	}
	return 0;
}	
