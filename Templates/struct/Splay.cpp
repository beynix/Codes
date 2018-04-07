struct Splay
{
    struct Node
    {
        // root ���ܻᱻ�޸ģ�ʹ��ָ��ָ���ָ��
        Node *fa, *ch[2], **root;
        // x ��ʾ����ڵ��ϵ���
        // size ��ʾ�����������������������Ĵ�С
        // cnt ��ʾ����� x �ж��ٸ�
        int x, size, cnt;

        Node(Node **root, Node *fa, int x) : root(root), fa(fa), x(x), cnt(1), size(1)
        {
            ch[0] = ch[1] = NULL; // ��Ҫ���ǳ�ʼ��
        }

        // �����ǰ�ڵ����丸�ڵ������ӣ����� 0 ���򷵻� 1
        int relation()
        {
            return this == fa->ch[0] ? 0 : 1;
        }

        void maintain()
        {
            size = cnt;
            if (ch[0]) size += ch[0]->size;
            if (ch[1]) size += ch[1]->size;
        }

        void rotate()
        {
            // �ɵĸ��ڵ�
            Node *old = fa;
            // ��תǰ��ǰ�ڵ��븸�ڵ�Ĺ�ϵ
            int r = relation();

            // ���� <--> ���ڵ�ĸ��ڵ�
            fa = old->fa;
            if (old->fa)
            {
                // ������ڵ��и��ڵ㣨���Ǹ�������ô�õ�ǰ�ڵ��滻���ڵ�ĸ��ڵ��и��ڵ��λ�õ�ָ��
                old->fa->ch[old->relation()] = this;
            }

            // ԭ�е���һ���ӽڵ� <--> ԭ�еĸ��ڵ�
            if (ch[r ^ 1])
            {
                ch[r ^ 1]->fa = old;
            }
            old->ch[r] = ch[r ^ 1]; // �ұߵ� ch[r ^ 1] �൱�� this->ch[r ^ 1]

            // ԭ�еĸ��ڵ� ��Ϊ������ӽڵ�
            old->fa = this;
            ch[r ^ 1] = old;

            // ����ά����Ϣ
            old->maintain();
            maintain();

            // ���ת���˸������´����ָ����ڵ��ָ��
            if (fa == NULL)
            {
                *root = this;
            }
        }

        // ��ת��ĳһ�ض�λ�ã�����ɾ��ʱ����̽ڵ���תΪ�����Ҷ���
        // target ΪĿ�길�ڵ㣬ȱʡ����Ϊ NULL������תֱ����Ϊ����û�и��ڵ㣩
        void splay(Node *target = NULL)
        {
            while (fa != target) // while (���ڵ㲻��Ŀ�길�ڵ�)
            {
                if (fa->fa == target) // ���ڵ�ĸ��ڵ���Ŀ�길�ڵ㣬ֱ��תһ��
                {
                    rotate();
                }
                else if (fa->relation() == relation()) // ��ϵ��ͬ����ת���ڵ㣬��ת����
                {
                    fa->rotate();
                    rotate();
                }
                else
                {
                    rotate();
                    rotate();
                }
            }
        }

        // ǰ����ȫ�� precursor �� predecessor
        Node *pred()
        {
            // �����������ҵ�
            Node *v = ch[0];
            while (v->ch[1]) v = v->ch[1];
            return v;
        }

        // ��̣�ȫ�� successor
        Node *succ()
        {
            // �������������
            Node *v = ch[1];
            while (v->ch[0]) v = v->ch[0];
            return v;
        }

        // ��һ���ڵ������������������С
        int rank()
        {
            return ch[0] ? ch[0]->size : 0;
        }
    } *root;

    Splay() : root(NULL)
    {
        insert(INT_MAX);
        insert(INT_MIN);
    }

    Node *insert(int x)
    {
        // v ��һ��ָ��ָ���ָ��
        // ��ʾҪ���뵽��λ��
        // ��� v ָ��һ����ָ��
        // ��ô�Ϳ��Բ��뵽����
        //
        // fa ���½ڵ�ĸ��ڵ�
        Node **v = &root, *fa = NULL;
        while (*v != NULL && (*v)->x != x) // ֱ���ҵ�һ����λ�ã������ҵ�ԭ�е�ֵΪ x �Ľڵ�
        {
            fa = *v;    // ����һ���ҵ��Ĳ��յ� v ��Ϊ���ڵ�
            fa->size++; // ��ΪҪ����������²���һ���µĽڵ�

            // ���ݴ�С��������������
            if (x < fa->x)
            {
                v = &fa->ch[0];
            }
            else
            {
                v = &fa->ch[1];
            }
        }

        if (*v != NULL)
        {
            (*v)->cnt++;
            (*v)->size++; // ��
        }
        else
        {
            (*v) = new Node(&root, fa, x);
        }

        (*v)->splay();

        // ��չ֮��*v ���λ�ô�Ŀ��ܲ������½ڵ㣨��Ϊ���ӹ�ϵ�ı��ˣ��� v һ��ָ��һ���ڵ��ĳ���ӽڵ��λ�ã�
        // ֱ�ӷ��ظ�
        return root;
    }

    Node *find(int x)
    {
        // �Ӹ��ڵ㿪ʼ��
        Node *v = root;
        while (v != NULL && v->x != x)
        {
            if (x < v->x)
            {
                v = v->ch[0];
            }
            else
            {
                v = v->ch[1];
            }
        }

        if (v) v->splay();
        return v;
    }

    // ɾ��һ���ڵ�
    void erase(Node *v)
    {
        Node *pred = v->pred(), *succ = v->succ();
        pred->splay();
        succ->splay(pred); // ʹ��̳�Ϊǰ�����������Ҷ���

        // ��ʱ��̵�����Ӽ�ΪҪɾ���Ľڵ� v���� v ��ʱΪҶ�ӽڵ�

        if (v->size > 1)
        {
            // ������ڲ�ֹһ�� x��ֻ�轫������һ
            v->size--;
            v->cnt--;
        }
        else
        {
            delete succ->ch[0]; // ʹ�� delete �ؼ��֣��ϸ��˵��new �� delete ����������ͷ� new ������ڴ�
            succ->ch[0] = NULL; // ��Ҫ�����ÿ�
        }

        // ɾ�˽ڵ㣬��Ҫ����С��С
        succ->size--;
        pred->size--;
    }

    // ɾ��һ����
    void erase(int x)
    {
        Node *v = find(x);
        if (!v) return; // û���ҵ�Ҫɾ�Ľڵ㣬ֱ�ӷ��أ�һ����Ŀ�в���������������

        erase(v);
    }

    // ��һ������ǰ��
    int pred(int x)
    {
        Node *v = find(x);
        if (v == NULL)
        {
            v = insert(x);
            int res = v->pred()->x;
            erase(v);
            return res;
        }
        else
        {
            return v->pred()->x;
        }
    }

    // ��һ�����ĺ��
    int succ(int x)
    {
        Node *v = find(x);
        if (v == NULL)
        {
            v = insert(x);
            int res = v->succ()->x;
            erase(v);
            return res;
        }
        else
        {
            return v->succ()->x;
        }
    }

    // ��һ����������
    int rank(int x)
    {
        Node *v = find(x);
        if (v == NULL)
        {
            v = insert(x);
            // ��ʱ v �Ѿ��Ǹ��ڵ��ˣ���Ϊ�²������ڵ�ᱻ��չ
            int res = v->rank(); // ��Ϊ��һ������С�����Բ���Ҫ +1
            erase(v);
            return res;
        }
        else
        {
            // ��ʱ v �Ѿ��Ǹ��ڵ��ˣ���Ϊ���ҵ��Ľڵ�ᱻ��չ
            return v->rank();
        }
    }

    // ��� k С����
    int select(int k)
    {
        Node *v = root;
        while (!(k >= v->rank() && k < v->rank() + v->cnt))
        {
            if (k < v->rank())
            {
                // Ҫ��ĵ� k �ȵ�ǰ�ڵ������С����Ҫ�������������в�ѯ
                v = v->ch[0];
            }
            else
            {
                k -= v->rank() + v->cnt;
                v = v->ch[1];
            }
        }
        v->splay();
        return v->x;
    }
} splay;
