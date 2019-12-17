
class List
{   
    private:
    
    class Node
    {
    public:
    int value;
    Node* next;

    Node(int value = 0, Node* next = nullptr)
    {
        this->value = value;
        this->next = next;
    }
    };

    public:
    Node* head;
    int size;

    List()
    {
        size = 0;
        head = nullptr;
    }

    int get_size()
    {
        return this->size;
    }

    int& operator[](const int index)
    {
        int counter = 0;
        Node* current = this->head;
        if (index < this->size)
        {
            while(current != nullptr)
            {
                if (counter == index)
                    return current->value;

                current = current->next;
                counter++;
            }
        }

        else
            std:: cout << "There is no such a node /n";
    }

    void push_back(int value)
    {
        if (this->head == nullptr)
            this->head = new Node(value);
        else
        {
            Node* current = this->head;
            while (current->next != nullptr)
                current = current->next;
            current->next = new Node(value);
        }
        this->size++;
    }

    Node* find_previous(int index)
    {
        Node* previous = this->head;
        for (int i = 0; i < index -1; i++)
            previous = previous->next;
    }

   void push_front(int value)
   {
 
        Node* newhead = new Node(value);
        newhead->next = this->head;
        this->head = newhead; 
        this->size++;
   }

    void pop_front()
    {

            Node* tmp = this->head;
            this->head = this->head->next;
            delete tmp;
            this->size --;    
    }

   
    
    void clear()
    {
        while (this->size > 0)
        {
            this->pop_front();
        }
    }


    ~List()
    {
       this->clear();
    }

    void insert(int value, int index)
    {
        if (index == 0)
            this->push_front(value);
        
        if (index < this->size)
        {
            Node* previous = this->head;
            for (int i = 0; i < index -1; i++)
                previous = previous->next;
        
            Node* tmp = previous->next;
            previous->next = new Node(value);
            previous->next->next = tmp;
            this->size++;
        }

        else 
            std:: cout << "Impossible to insert a node with such index \n";
    }

    void remove(int index)
    {
        if (index == 0)
            this->pop_front();  
        
        if(index < this->size)
        {
            Node* previous = this->head;
            for (int i = 0; i < index -1; i++)
                previous = previous->next;
        
            Node* tmp = previous->next;
            previous->next = tmp->next;
            delete tmp;
            this->size--;
        }

        else
            std:: cout << "Impossible to delete a node with such index \n";    
        
    }
    
    void pop_back()
    {
        this->remove(this->size - 1);
    }

};
