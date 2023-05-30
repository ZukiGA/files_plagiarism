public class LinkedList {

    private Node head;

    private static class Node {
        private int data;
        private Node next;

        Node(int data) {
            this.data = data;
            next = null;
        }
    }

    public void printList() {
        Node currentNode = head;
        while (currentNode != null) {
            System.out.print(currentNode.data + " ");
            currentNode = currentNode.next;
        }
        System.out.println();
    }

    public void insert(int data) {
        Node newNode = new Node(data);
        if (head == null) {
            head = newNode;
        } else {
            Node currentNode = head;
            while (currentNode.next != null) {
                currentNode = currentNode.next;
            }
            currentNode.next = newNode;
        }
    }

    public void delete(int data) {
        if (head == null) {
            return;
        }

        if (head.data == data) {
            head = head.next;
            return;
        }

        Node currentNode = head;
        Node prevNode = null;
        while (currentNode != null && currentNode.data != data) {
            prevNode = currentNode;
            currentNode = currentNode.next;
        }

        if (currentNode == null) {
            return;
        }

        prevNode.next = currentNode.next;
    }

    public boolean search(int data) {
        Node currentNode = head;
        while (currentNode != null) {
            if (currentNode.data == data) {
                return true;
            }
            currentNode = currentNode.next;
        }
        return false;
    }

    public static void main(String[] args) {
        LinkedList linkedList = new LinkedList();

        linkedList.insert(1);
        linkedList.insert(2);
        linkedList.insert(3);
        linkedList.insert(4);
        linkedList.insert(5);

        System.out.print("Linked List: ");
        linkedList.printList();

        System.out.println("Search for 3: " + linkedList.search(3));
        System.out.println("Search for 6: " + linkedList.search(6));

        linkedList.delete(3);
        System.out.print("Linked List after deletion: ");
        linkedList.printList();
    }
}
