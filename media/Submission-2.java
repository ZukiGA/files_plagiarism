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

    public void printListReverse() {
        printReverse(head);
        System.out.println();
    }

    private void printReverse(Node node) {
        if (node == null) {
            return;
        }
        printReverse(node.next);
        System.out.print(node.data + " ");
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

        linkedList.insert(2);
        linkedList.insert(4);
        linkedList.insert(5);
        linkedList.insert(7);
        linkedList.insert(8);

        System.out.print("Reverse Linked List: ");
        linkedList.printListReverse();

        System.out.println("Search 4: " + linkedList.search(4));
        System.out.println("Search 5: " + linkedList.search(5));
    }
}
