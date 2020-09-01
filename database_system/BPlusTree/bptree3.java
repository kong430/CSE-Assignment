import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.io.ObjectOutputStream;

public class bptree3 implements Serializable{
	private static final long serialVersionUID = 1L;
	static FileOutputStream fos = null;
	static ObjectOutputStream oos = null;
	static int b; //max # of child nodes, so max key num is b-1
	//static Node root = new Node(1, b-1);
	
	public static class Node implements Serializable{
		private static final long serialVersionUID = 1L;
		boolean is_leaf;
		int Max_size;
		Node parent;
		int m; //# of keys
		ArrayList<Pair> p; //an array of b <key, value> pairs
		Node r; //pointer to the right
		int value;
		
		public Node() {	}
		
		public Node(int v) {
			this.value = v;
		}
		
		public Node(int v, int size) {
			this.m = 0;
			this.Max_size = size;
			this.p = new ArrayList<Pair>(size+1); 
			this.parent = null;
		}
	}
	
	public static class Pair implements Serializable{
		private static final long serialVersionUID = 1L;
		public int key;
		public Node node;
		
		public Pair() {}
		public Pair(int k, Node n) {
			this.key = k;
			this.node = n;
		}
	}
	
	public static class Sort implements Serializable{
		private static final long serialVersionUID = 1L;
		
		public Sort() {}
		
		public int add_index(Node nd, int k) {
			int i;
			if (nd.m==0) return 0;
			for (i=0;i<nd.m;i++) {
				if (nd.p.get(i).key<k) continue;
				else break;
			}
			return i;
		}
	}
	
	static Node root = null;
	static Sort sort = new Sort();
	
	public static boolean is_root(Node nd) {
		if (nd.parent==null) return true;
		else return false;
	}
	
	public static Node Create(int size) {
		root = new Node(1, size);
		root.is_leaf = true;
		root.m = 0;
		root.Max_size = size;
		root.parent = null;
		b = size;
		return root;
	}

	public static Node Search_leaf(Node n, int k) {
		if (n.is_leaf==true) return n;
		else {
			for (int i=0;i<n.m;i++) {
				if (k>n.p.get(n.m-1).key) return Search_leaf(n.r, k);
				else if (k<n.p.get(i).key) {
					return Search_leaf(n.p.get(i).node, k);
				}
				else continue;
				}
			}
		return null;
	}
	
	public static void Insert(Node nd, int k, int v) {
		Node tmp = new Node(1, b-1);
		tmp = Search_leaf(nd, k);
		Node value_node = new Node(v);
		int addIndex;
		//when there is space in leaf node
		if (tmp.m < b-1) {
			if (is_root(tmp)==true) root = tmp;
			addIndex = sort.add_index(tmp, k);
			tmp.p.add(addIndex, new Pair(k, value_node));
			tmp.m++;
		}
		//when there is no space in leaf node
		//tmp.m == b-1
		else {
			//when insert node is root
			if (is_root(tmp)==true) {
				addIndex = sort.add_index(tmp, k);
				tmp.p.add(addIndex, new Pair(k, value_node));
				tmp.m++;
		
				int index = tmp.m/2;
				
				Node new_left = new Node(1, b-1);
				Node new_right = new Node(1, b-1);
				new_left.is_leaf = new_right.is_leaf = true;
				new_left.parent = new_right.parent = tmp;
				new_left.r = new_right;
	
				for (int i=0;i<index;i++) {
					new_left.p.add(new Pair(tmp.p.get(i).key, tmp.p.get(i).node));
					new_left.m++;
				}
					
				for (int i=index;i<tmp.m;i++) {
					new_right.p.add(new Pair(tmp.p.get(i).key, tmp.p.get(i).node));
					new_right.m++;
				}
					
				for (int i=0;i<index;i++) {
					tmp.p.remove(0);
					tmp.m--;
				}
				while (tmp.m!=1) {
					tmp.p.remove(1);
					tmp.m--;
				}
				
				tmp.is_leaf = false;
				tmp.p.get(0).node = new_left;
				tmp.r = new_right;
				root = tmp;
			}
			//when insert node is not root
			else {
				//when insert node's parent has space to insert
				if (tmp.parent.m<b-1) {
					addIndex = sort.add_index(tmp, k);
					tmp.p.add(addIndex, new Pair(k, value_node));
					tmp.m++;
					
					int index = tmp.m/2;
					
					Node new_right = new Node(1, b-1);
					new_right.parent = tmp.parent;
					new_right.is_leaf = true;
					
					for (int i=index;i<tmp.m;i++) {
						new_right.p.add(new Pair(tmp.p.get(i).key, tmp.p.get(i).node));
						new_right.m++;
					}
					while (tmp.m>index) {
						tmp.p.remove(index);
						tmp.m--;
					}
					
					new_right.r = tmp.r;
					tmp.r = new_right;
					
					Pair newToParent = new Pair(new_right.p.get(0).key, new_right.p.get(0).node);
					addIndex = sort.add_index(tmp.parent, k);
					if(addIndex==tmp.parent.m-1) tmp.parent.r = new_right;
					tmp.parent.p.add(addIndex, newToParent);
					tmp.parent.m++;
					
					int ParentIndexOfNew = tmp.parent.p.indexOf(newToParent);
					if (ParentIndexOfNew == 0) {
						newToParent.node = tmp.parent.p.get(ParentIndexOfNew+1).node;
						tmp.parent.p.get(ParentIndexOfNew+1).node = newToParent.node.r;
					}
					else newToParent.node = tmp.parent.p.get(ParentIndexOfNew-1).node.r;
					
					Node tmpNd = newToParent.node.r;
					for (int i=ParentIndexOfNew+1;i<=tmp.parent.m;i++) {
						if (i==tmp.parent.m) {
							//tmp.parent.r = tmp.parent.p.get(ParentIndexOfNew).node.r;
							tmp.parent.r = tmpNd;
							break;
						}
						tmp.parent.p.get(i).node = tmpNd;
						if (tmpNd.r != null) tmpNd = tmpNd.r;
					}
				}
				//when insert node's parent has no space
				else {
					addIndex = sort.add_index(tmp, k);
					tmp.p.add(addIndex, new Pair(k, value_node));
					tmp.m++;
					
					while (tmp.m==b) {
						Pair newToParent = null;
						int index = tmp.m/2;
						
						Node new_right = new Node(1, b-1);
						
						if (tmp.parent!=null) new_right.parent = tmp.parent;
						if (tmp.is_leaf == true) new_right.is_leaf = true;
						
						for (int i=index;i<tmp.m;i++) {
							new_right.p.add(new Pair(tmp.p.get(i).key, tmp.p.get(i).node));
							new_right.m++;
						}
						
						while (tmp.m>index) {
							tmp.p.remove(index);
							tmp.m--;
						}
						
						if (tmp.is_leaf == true) {
							if (tmp.r!=null) new_right.r = tmp.r;
							tmp.r = new_right;
						}
						else {
							new_right.r = tmp.r;
							tmp.r = new_right.p.get(0).node;
						}

						//when tmp is root, make new root
						if (is_root(tmp)==true) {
							Node newParentNd = new Node(1, b-1);
							tmp.parent = new_right.parent = newParentNd;
							root = tmp.parent;
						}
								
						newToParent = new Pair(new_right.p.get(0).key, new_right.p.get(0).node);
						addIndex = sort.add_index(tmp.parent, k);
						tmp.parent.p.add(addIndex, newToParent);
						tmp.parent.m++;
						
						if (tmp.is_leaf == false) {
							new_right.p.remove(0);
							new_right.m--;
							for (int i=0;i<=new_right.m;i++) {
								if (i==new_right.m) {
									new_right.r.parent = new_right; 
									break;
								}
								new_right.p.get(i).node.parent = new_right;
							}
						}
						
						int ParentIndexOfNew = tmp.parent.p.indexOf(newToParent);
						if (tmp.parent.m==1) {
							tmp.parent.p.get(0).node = tmp;
							tmp.parent.r = new_right;
						}
						else {
							if (ParentIndexOfNew == 0 ) newToParent.node = tmp.parent.p.get(ParentIndexOfNew+1).node;
							else newToParent.node = tmp.parent.p.get(ParentIndexOfNew-1).node.r;
						
							Node tmpNd;
							if (tmp.is_leaf == false) {
								tmp.parent.p.get(ParentIndexOfNew).node = tmp;
								if (ParentIndexOfNew==tmp.parent.m-1) {
									tmp.parent.r = new_right;
								}
								else tmp.parent.p.get(ParentIndexOfNew+1).node = new_right;
							}
			
							else {
								tmpNd = newToParent.node.r;
								for (int i=ParentIndexOfNew+1;i<=tmp.parent.m;i++) {
									if (i==tmp.parent.m && tmp.is_leaf ==true) {
										tmp.parent.r = tmp.parent.p.get(i-1).node.r;
										break;
									}
									tmp.parent.p.get(i).node = tmpNd;
									if (tmpNd.r != null) tmpNd = tmpNd.r;
								}
							}
						}
						tmp = tmp.parent;
					}
				}
			}
		}
	}
	
	public static void Delete(Node nd, int k) {}
	
	//if return value is -1, print "NOT FOUND"
	public static int Single_Key_Search(Node root, int k) {
		Node tmp = new Node(1, b-1);
		tmp = root;
		
		if (root.is_leaf==true) {
			for (int i=0;i<tmp.m;i++) {
				if (k==tmp.p.get(i).key) return (tmp.p.get(i).node.value);
				else continue;
			}
			return -1;
		}
	
		//print all keys in the node when tmp changes
		else {
			while (tmp.is_leaf==false) {
				for (int i=0;i<tmp.m;i++) {
					System.out.print(tmp.p.get(i).key);
					if (i!=tmp.m-1) System.out.print(", ");
				}
				System.out.print("\n");
				for (int i=0;i<=tmp.m;i++) {
					if (i==tmp.m) {
						tmp = tmp.r;
						break;
					}
					else if (k>=tmp.p.get(i).key) continue; 
					else {
						tmp = tmp.p.get(i).node;
						break;
					}
				}		
			}
		}
		//Search k in the leafNode, if not exists, return -1
		for (int i=0;i<tmp.m;i++) {
			if (k==tmp.p.get(i).key) {
				return tmp.p.get(i).node.value;
			}
			else continue;
		}
		return -1;
	}
	
	public static ArrayList<Integer> Ranged_Search(Node root, int start, int end) {
		ArrayList<Integer> ranged_value = new ArrayList<Integer>();
		Node tmp = new Node(1, b-1);
		tmp = root;
		
		//find start node
		while (tmp.is_leaf==false) {
			for (int i=0;i<=tmp.m;i++) {
				if (i==tmp.m) {
					tmp = tmp.r;
					break;
				}
				else if (start<tmp.p.get(i).key) {
					tmp = tmp.p.get(i).node;
					break;
				}
				else continue;
			}
		}
		
		while (true) {
			if (tmp.p.get(0).key>end) break;
			for (int i=0;i<tmp.m;i++) {
				if (tmp.p.get(i).key>=start && tmp.p.get(i).key<=end) {
					ranged_value.add(tmp.p.get(i).node.value);
					System.out.println(tmp.p.get(i).key + ", "+tmp.p.get(i).node.value);
				}
			}
			if (tmp.r!=null) tmp = tmp.r;
			else break;
		}
		return ranged_value;
	}

	public static void main(String[] args) {
		String type = new String(args[0]);
		String index_file = new String(args[1]);
		String file_name = new String();
		int searchKey_Num = 0;
		int Range_start = 0;
		int Range_end = 0;
		FileInputStream fis;
		try {
			fis = new FileInputStream(index_file);
			ObjectInputStream ois = new ObjectInputStream(fis);
			if (type!="-c") {
				root = (Node) ois.readObject();
				b = root.Max_size;
				ois.close();
			}
		} catch (Exception e1) {
			e1.printStackTrace();
		}
		if (args.length == 3) {
			//when create
			if (type.equalsIgnoreCase("-c")) b = Integer.parseInt(args[2]);
			//when insert or delete
			else if (type.equalsIgnoreCase("-i") || type.equalsIgnoreCase("-d")) file_name = args[2];
			else searchKey_Num = Integer.parseInt(args[2]);
		}
		else if (args.length == 4) {
			Range_start = Integer.parseInt(args[2]);
			Range_end = Integer.parseInt(args[3]);
		}
		if (type.equalsIgnoreCase("-c")) {
			root = Create(b);
			try {
				fos = new FileOutputStream(index_file);
				oos = new ObjectOutputStream(fos);
			}catch(IOException e){
				System.out.println("Not found file");
			}
		}
		else if (type.equalsIgnoreCase("-i")) {
			int[][] index =  new int[100000][3];
			try {
				fos = new FileOutputStream(index_file);
				oos = new ObjectOutputStream(fos);
				File csv = new File(file_name);
				BufferedReader br = new BufferedReader(new FileReader(csv));
				String line = "";
				int row = 0;
				while ((line = br.readLine())!=null) {
					String[] token = line.split(",", -1);
					index[row][0] = Integer.parseInt(token[0]);
					index[row][1] = Integer.parseInt(token[1]);
									
					Insert(root, index[row][0], index[row][1]);
					row++;
				}
				br.close();
			}catch(FileNotFoundException e) {
				e.printStackTrace();
			}catch(IOException e) {
				e.printStackTrace();
			}
		}
		else if (type.equalsIgnoreCase("-d")) {
			int[][] index =  new int[100000][3];
			try {
				fos = new FileOutputStream(index_file);
				oos = new ObjectOutputStream(fos);
				File csv = new File(file_name);
				BufferedReader br = new BufferedReader(new FileReader(csv));
				String line = "";
				int row = 0;
				while ((line = br.readLine())!=null) {
					String[] token = line.split(",");
					index[row][0] = Integer.parseInt(token[0]);
					row++;
					
					Delete(root, index[row][0]);
				}
				br.close();
			}catch(FileNotFoundException e) {
				e.printStackTrace();
			}catch(IOException e) {
				e.printStackTrace();
			}
		}
		else if (type.equalsIgnoreCase("-s")) {
			try {
				fos = new FileOutputStream(index_file);
				oos = new ObjectOutputStream(fos);
			} catch (Exception e) {
				e.printStackTrace();
			}
			
			int value = Single_Key_Search(root, searchKey_Num);
			if (value == -1) System.out.println("NOT FOUND");
			else System.out.println(value);
		}
		else if (type.equalsIgnoreCase("-r")) {
			try {
				fos = new FileOutputStream(index_file);
				oos = new ObjectOutputStream(fos);
			} catch (Exception e) {
				e.printStackTrace();
			}
			Ranged_Search(root, Range_start, Range_end);
		}
		else {
			System.out.println("Not valid Command Type");
		}
		try {
			oos.writeObject(root);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			oos.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
