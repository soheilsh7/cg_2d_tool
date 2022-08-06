class vertex;
class edge;
class face;


int vertex_n=0, edge_n=0, face_n=0;
class vertex
{
private:
    int key;
public:

    float x, y;

    vertex(float in_x=0, float in_y=0)
    {
        key = vertex_n;
        vertex_n ++;
        add(in_x,in_y);
    }

    ~vertex()
    {
        //vertex_n --;
    }

    int get_key()
    {
        return key;
    }

    void set_key(int sk)
    {
        key = sk;
    }

    void print()
    {
        std::cout << "point " << key << " coordinates : x = " << x << " y = " << y << std::endl;
    }

    void add(float in_x, float in_y)
    {
        x = in_x;
        y = in_y;
    }

};

class edge
{
private:
    int key;
public:
    vertex *start_vertex, *end_vertex;
    // edge *twin; //for half_edge
    edge *next, *previous;
    face *left_face, *right_face;

    edge(vertex *start, vertex *end)
    {
        start_vertex = start;
        end_vertex = end;
        key = edge_n;
        edge_n ++;
    }

    ~edge()
    {
        //edge_n --;
    }

    int get_key()
    {
        return key;
    }

    void set_key(int sk)
    {
        key = sk;
    }

    void print()
    {
        std::cout << "edge " << key << " points : \np " << start_vertex->get_key() << "\tp " << end_vertex->get_key() <<std::endl;
    }

    void add(vertex *start, vertex *end, face *right, face *left)
    {
        start_vertex = start;
        end_vertex = end;
        left_face = left;
        right_face = right;
    }
};

class face
{
private:
    int key;
public:
    vector<vertex *> vertexes ; //= vector<vertex *>(3);
    vector<edge *> edges ; // = vector<edge *>(3);

    face()
    {
        key = face_n;
        face_n ++;
    }

    ~face()
    {
        //face_n --;
    }

    void add_vertex(vertex* v)
    {
        bool add = true;

        for (int i=0; i<vertexes.size(); i++)
        {
            if(vertexes[i]->get_key() == v->get_key())
                add = false;
        }

        if (add)
        {
            vertexes.push_back(v);
        }
    }

    void add_edge(edge* e)
    {
        bool add = true;

        for (int i=0; i<edges.size(); i++)
        {
            if(edges[i]->get_key() == e->get_key())
                add = false;
        }

        if (add)
        {
            edges.push_back(e);
            add_vertex(e->start_vertex);
            add_vertex(e->end_vertex);
        }
    }

    void add_vertex_vector(vector<vertex *> v)
    {
       for (int i=0; i<v.size(); i++)
        {
            vertexes.push_back(v[i]);
        }

    }

    void add_edge_vector(vector<edge *> e)
    {
       for (int i=0; i<e.size(); i++)
        {
            edges.push_back(e[i]);
        }

    }


    void print()
    {
        std::cout << "face " << key << " vertexes :" <<std::endl;
        std::cout << vertexes.size() << " Vertexes" << std::endl;

        for (int i=0; i<vertexes.size(); i++)
        {
            std::cout << "p " << vertexes[i]->get_key() << "\t";
        }
        std::cout << std::endl;
        

        std::cout << "face " << key << " edges :" <<std::endl;
        for (int i=0; i<edges.size(); i++)
        {
            std::cout << "e " << edges[i]->get_key() << "\t";

        }
        std::cout << std::endl;
        
    }
    

};

