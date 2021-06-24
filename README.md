toanroiractantanh
Hello!!!Xin chào các bạn. Đây là thư viện chạy các thuật toán trong môn toán rời rạc.
Được chia làm 3 thư viện nhỏ;

Thư viện 1: coloring.h ,prufercode.h:
  coloring.h: tô màu đồ thị, đọc file color.txt, xuất ra file color.dot
  prufercode.h: nén cây, đọc từ file prufer.txt, hiện thị mã prufer, father ra chương trình
Thư viện 2: graph.h dfsbfs.h krukal.h,prim.h đọc dữ liệu từ file graph.txt
  graph.h: Tạo đồ thị bằng thư viện JRB jval.c dllist.c jrb.c 
  link thu vien JRB: http://web.eecs.utk.edu/~huangj/cs360/360/notes/Libfdr/?fbclid=IwAR0CTeIMbt_b_RSs9Wfn4h7L91IeSSr-YvEI6v2XmDMEIzfhH6ybtWC8mPc
  hàm tìm thành phần liên thông đồ thị vô hướng lienthongdothivohuong(g)
  hàm tìm thành phần liên thông đồ thị có hướng lienthongmanh(g)
  graphiz_vh truyền vào đồ thị vô hướng xuất ra file graph_vh.dot
  graphiz_ch truyền vào đồ thị có hướng xuất ra file graph_ch.dot
  dfsbfs.h: Duyệt và in ra đồ thị bằng BFS,DFS;
  krukal.h: Tìm cây khung nhỏ nhất bằng thuật toán krukal. Xuất ra file cây bao trum nho nhat mst.dot. In ra các cạnh thuộc cây khung,độ dài cây khung.
  prim.h: Tìm cây khung nhỏ nhất bằng thuật toán prim. In ra các cạnh thuộc cây khung,độ dài cây khung.

Thư viện 3: graph.h dagtopo.h dijkbell.h
  graph.h:Giống thư viện 2.
  dagtopo.h: Kiểm tra đồ thị có phi chu trình không(DAG) và in ra sắp xếp Topologicalsor.
  dijkbell.h: Tìm đường đi ngắn nhất bằng thuật toán dijkstra và bellman.Xuất ra file đồ thị dijkstra.dot

Tác giả Việt, Dũng , Việt Anh
               
              
               
