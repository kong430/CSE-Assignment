import java.sql.*;
import java.util.Scanner;

public class MusicApp {	
	static Scanner scan = new Scanner(System.in);
	static int input;
	static String input_s;
	static int USER_NUM=1, REGISTER_NUM=1, MANAGER_NUM=1;
	static String name, sex, bdate, address, email, id, password;
	static int coin, user_num;
	static String genre, album, release_date, lyricist, composer, title, artist, chart_name;
	static int chartscore, price, register_num, manager_num;
	static String rrn;
	static String[] GENRE = {"ballade", "dance", "classic", "agitation", "etc"};
	
	static Connection conn = null;

	public static void ini_USERNUM() {
		Statement stmt = null;
		ResultSet rs = null;
		
		try {
			String query = "select MAX(user_num) from user_";
			
			stmt = conn.createStatement();
			rs = stmt.executeQuery(query);		
			
			if (rs.next()) {
				USER_NUM = rs.getInt(1);
			}
			if (rs!=null) try {rs.close();}catch(SQLException e) {e.printStackTrace();}
			if (stmt!=null) try {stmt.close();}catch(SQLException e) {e.printStackTrace();}
			
		}catch (SQLException e) {
			e.printStackTrace();
		}
 	}
	
	public static void ini_REGISTERNUM() {
		Statement stmt = null;
		ResultSet rs = null;
		
		try {
			String query = "select MAX(register_num) from music";
			
			stmt = conn.createStatement();
			rs = stmt.executeQuery(query);		
			
			if (rs.next()) {
				REGISTER_NUM = rs.getInt(1);
			}
			if (rs!=null) try {rs.close();}catch(SQLException e) {e.printStackTrace();}
			if (stmt!=null) try {stmt.close();}catch(SQLException e) {e.printStackTrace();}
		}catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public static void music_cnt() {
		PreparedStatement pstmt = null;
		Statement stmt = null;
		ResultSet rs = null;
		try {
			String query1 = "select chart.music_cnt from chart where chart.chart_name='TopChart'";
			String query2 = "update chart set music_cnt=?";
			
			pstmt = conn.prepareStatement(query2);
			stmt = conn.createStatement();
			rs = stmt.executeQuery(query1);
			int originCnt=0;
			if (rs.next()) {
				originCnt = rs.getInt(1);
			}
			
			pstmt.setInt(1, originCnt+1);
			pstmt.execute();
		
			if (rs!=null) try {rs.close();} catch(SQLException e) {};
			if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
			return;
			
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
 	public static void startMenu() {
 		System.out.println("-----------------");
 		System.out.println("0. Exit");
		System.out.println("1. User Menu");
		System.out.println("2. Manager Menu");
		System.out.println("-----------------");
		System.out.print("Input: ");
		input = scan.nextInt();
		System.out.print('\n');
		switch(input) {
		case 0:
			System.exit(0);
			break;
		case 1:
			userMenu();
			break;
		case 2:
			managerMenu();
			break;
		default:
			System.out.println("Invalid input, Select again\n");
			startMenu();
			break;
		}
 	}
 	
 	public static void userMenu() {
 		System.out.println("-----------------------");
 		System.out.println("0. Return to Main Menu");
		System.out.println("1. Register New User");
		System.out.println("2. Log in as User");
		System.out.println("-----------------------");
		System.out.print("Input: ");
		input = scan.nextInt();
		System.out.print('\n');
		switch(input) {
		case 0:
			startMenu();
			break;
		case 1:
			user_reg();
			break;
		case 2:
			user_log();
			break;
		default:
			System.out.println("Invalid input, Select again\n");
			userMenu();
			break;
		}
 	}
 	
 	public static void user_reg() {
		System.out.print("Name: ");
		name = scan.next();
		System.out.print("Sex(f or m): ");
		sex= scan.next();
		System.out.print("Birthdate: ");
		bdate = scan.next();
		System.out.print("Address: ");
		address = scan.next();
		System.out.print("Email: ");
		email = scan.next();
		System.out.print("ID: ");
		id = scan.next();
		System.out.print("Password: ");
		password = scan.next();
		coin = 0;
		user_num = ++USER_NUM;
		manager_num = user_num%5;
		if (user_num%5==0) manager_num = 5;
		
		PreparedStatement pstmt =null;
		
		try {
			String query = "insert into user_(name_, sex, bdate, address, email, id, password_, user_num, coin, manager_num) values(?,?,?,?,?,?,?,?,?,?)";
			
			pstmt = conn.prepareStatement(query);
			
			pstmt.setString(1, name);
			pstmt.setString(2, sex);
			pstmt.setString(3, bdate);
			pstmt.setString(4, address);
			pstmt.setString(5, email);
			pstmt.setString(6, id);
			pstmt.setString(7, password);
			pstmt.setInt(8, user_num);
			pstmt.setInt(9, coin);
			pstmt.setInt(10, manager_num);
			
			int r = pstmt.executeUpdate();
			System.out.println("\n"+r+" user newly registered, user_num is "+user_num);
			if (pstmt!=null) try {pstmt.close();}catch(Exception e) {e.printStackTrace();}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		try {
			String query = "insert into playlist(user_num, playlist_num) values(?,?)";
			
			pstmt = conn.prepareStatement(query);
			
			pstmt.setInt(1, user_num);
			pstmt.setInt(2, user_num);
			
			int r = pstmt.executeUpdate();
			System.out.println(r +" playlist added\n");
			if (pstmt!=null) try {pstmt.close();}catch(Exception e) {e.printStackTrace();}
			userMenu();
			return;
			} catch (SQLException e) {
				e.printStackTrace();
			}
 	}
 	
 	public static void user_log() {
 		System.out.print("User_num: ");
		user_num = scan.nextInt();
		System.out.print("ID: ");
		id = scan.next();
		System.out.print("Password: ");
		password = scan.next();
	
		Statement stmt = null;
		ResultSet rs = null;
		
		try {
			String query = "select user_.name_, user_.sex, user_.bdate, user_.address, user_.email, user_.id, user_.password_, user_.user_num, user_.coin, user_.manager_num from user_ where user_.user_num="+user_num
				+ " and user_.id='"+id+"' and user_.password_='"+password+"'";
			
			stmt = conn.createStatement();
			rs = stmt.executeQuery(query);		
			
			if (rs.next()) {
				name = rs.getString(1);
				sex = rs.getString(2);
				bdate = rs.getString(3);
				address = rs.getString(4);
				email = rs.getString(5);
				id = rs.getString(6);
				password = rs.getString(7);
				user_num = rs.getInt(8);
				coin = rs.getInt(9);
				manager_num = rs.getInt(10);
				
				System.out.println("Log in as id: "+id+"\n");
				if (stmt!=null) try {stmt.close();}catch(SQLException e) {e.printStackTrace();}
				after_userlog();
				return;
			}
			else {
				System.out.println("There is No such User\n");
				if (stmt!=null) try {stmt.close();}catch(SQLException e) {e.printStackTrace();}
				userMenu();
				return;
			}
			
		}catch (SQLException e) {
			e.printStackTrace();
		}
 	}

 	public static void after_userlog() {
 		Statement stmt = null;
 		ResultSet rs = null;
 		PreparedStatement pstmt = null;
 		System.out.println("-----------------------------");
 		System.out.println("0. Log out");
 		System.out.println("1. View Chart");
		System.out.println("2. View Music");
		System.out.println("3. View Playlist");
		System.out.println("4. View Coin");
		System.out.println("5. Charge Coin");
		System.out.println("6. Add new music to Playlist");
		System.out.println("7. Delete music from Playlist");
		System.out.println("8. View User Information");
		System.out.println("9. Withdraw from App");
		System.out.println("-----------------------------");
		System.out.print("Input: ");
		input = scan.nextInt();
		System.out.print('\n');
		switch(input) {
		case 0:
			userMenu();
			return;
		case 1:
			//차트 확인
			stmt = null;
			rs = null;
			try {	
				String query = "select music.title, music.artist, music.chartscore from chart, music where not music.chartscore=0 order by music.chartscore desc";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				int cnt =1;

				System.out.println("--------------------------------------------------------------------------------");
				System.out.println("Rank\t\t\t"+"Title\t\t\t"+"Artist\t\t\t"+"Score");
				System.out.println("--------------------------------------------------------------------------------");
				
				while (rs.next()) {
					System.out.printf("%-24d", cnt);
					System.out.printf("%-24s", rs.getString(1));
					System.out.printf("%-24s", rs.getString(2));
					System.out.printf("%-24s", rs.getInt(3));
					System.out.print("\n");
					cnt++;
				}
				System.out.println("--------------------------------------------------------------------------------");
				System.out.print("\n");
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				after_userlog();
				return;
			} catch (SQLException e) {
				e.printStackTrace();
			}

		case 2:
			//모든 음악 확인
			stmt = null;
			rs = null;
			try {
				String query = "select music.title, music.artist from music";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				
				int cnt=0;
				System.out.println("------------------------------------");
				System.out.println("Title\t\t\t"+"Artist\t\t\t");
				System.out.println("------------------------------------");
				
				while (rs.next()) {
					cnt++;
					System.out.printf("%-24s", rs.getString(1));
					System.out.printf("%-24s", rs.getString(2));
					System.out.print("\n");
				}
				System.out.println("------------------------------------");
				System.out.print('\n');
				if (cnt==0) {
					if (rs!=null) try {rs.close();} catch(SQLException e) {};
					if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
					after_userlog();
					return;
				}
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
			try {
				System.out.println("To see more Detailed information, enter the title. If not, enter '0'");
				System.out.print("Input: ");
				String mtitle = scan.nextLine();
				mtitle = scan.nextLine();
				if (mtitle.equals("0")) {
					System.out.println("\n");
					after_userlog();
					return;
				}
				
				String query = "select music.genre, music.album, music.release_date, music.lyricist, music.composer, music.title, music.artist, music.chartscore, music.price, music.register_num "
						+ "from music where music.title='"+mtitle+"'";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
	
				if (rs.next()) {
					System.out.println("\nGenre: "+rs.getString(1));
					System.out.println("Album: "+rs.getString(2));
					System.out.println("Release_date: "+rs.getString(3));
					System.out.println("Lyricist: "+rs.getString(4));
					System.out.println("Composer: "+rs.getString(5));
					System.out.println("Title: "+rs.getString(6));
					System.out.println("Artist: "+rs.getString(7));
					System.out.println("ChartScore: "+rs.getInt(8));
					System.out.println("Price: "+rs.getInt(9));
					System.out.println("Register_num : "+rs.getInt(10)+'\n');
				}
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
			
				after_userlog();
				return;
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		case 3:
			stmt = null;
			rs = null;
			try {
				String query = "select music.title, music.artist from reg_in_pla, music where reg_in_pla.user_num="+user_num+" and reg_in_pla.register_num=music.register_num";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);

				System.out.println("------------------------------------");
				System.out.println("Title\t\t\t"+"Artist");
				System.out.println("------------------------------------");
				while (rs.next()) {
					String mtitle = rs.getString(1);
					String martist = rs.getString(2);
					System.out.printf("%-24s", mtitle);
					System.out.printf(martist+'\n');			
				}
				System.out.println("------------------------------------");
				System.out.print("\n");
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				after_userlog();
				return;	
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		case 4:
			//내 coin 확인
			stmt = null;
			rs = null;
			try {	
				String query = "select user_.coin from user_ where user_.user_num="+user_num;
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				
				if (rs.next()) {
					String usrcoin = rs.getString(1);
					System.out.println("Coin: "+usrcoin+'\n');
				}
				
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
		
				after_userlog();
				return;
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		case 5:
			//coin 충전
			System.out.println("How much do you want to charge?");
			int wantCoin = scan.nextInt();
			pstmt = null;
			stmt = null;
			rs = null;
			try {
				String query1 = "select user_.coin from user_ where user_.user_num="+user_num;
				String query2 = "update user_ set coin=? where user_num="+user_num;
				
				pstmt = conn.prepareStatement(query2);
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query1);
				int originCoin=0;
				if (rs.next()) {
					originCoin = rs.getInt(1);
				}
				
				pstmt.setInt(1, originCoin+wantCoin);
				pstmt.execute();
				coin = originCoin+wantCoin;
				System.out.println("Coin successfully Charged!\n");
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				after_userlog();
				return;
				
			} catch (SQLException e) {
				e.printStackTrace();
			}

		case 6:
			//playlist에 음악 추가
			if (coin<1000) {
				System.out.println("Not enough Coin, you can't buy Music\n");
				after_userlog();
				return;
			}
			stmt = null;
			rs = null;
			try {
				String query = "select music.title, music.artist, music.register_num from music";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				
				System.out.println("----------------------------------------------------------------");
				System.out.println("Title\t\t\t"+"Artist\t\t\t"+"Register number\t\t\t");
				System.out.println("----------------------------------------------------------------");
			
				while (rs.next()) {
					System.out.printf("%-24s", rs.getString(1));
					System.out.printf("%-24s", rs.getString(2));
					System.out.printf("%-24s", rs.getInt(3));
					System.out.print("\n");
				}
				System.out.println("----------------------------------------------------------------");
				System.out.print('\n');
			} catch (SQLException e) {
				e.printStackTrace();
			}finally {
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				}
			
			pstmt = null;
			stmt = null;
			rs = null;
			int mnumber = 0;
			try {
				System.out.print("Select Music by Register Number to add to Playlist\ninput: ");
				mnumber = scan.nextInt();
		
				String query = "insert into reg_in_pla (register_num, user_num, playlist_num) values ("+mnumber+", "+user_num+", "+user_num +") on duplicate key update reg_in_pla.register_num= "
						+ mnumber+", reg_in_pla.user_num="+user_num+", reg_in_pla.playlist_num="+user_num;
						
			
				stmt = conn.createStatement();
				int r = stmt.executeUpdate(query);

				if (r>0) {
					System.out.println("\nSuccessfully Added\n");
					if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				}
				else {
					System.out.println("Adding fail\n");
					if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
					after_userlog();
					return;
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
			try {
				String query = "insert into buy_music (register_num, user_num) values ("+mnumber+", "+user_num+") on duplicate key update buy_music.register_num= "
						+ mnumber+", buy_music.user_num="+user_num;
						
				stmt = conn.createStatement();
				int r = stmt.executeUpdate(query);

				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
			} catch (SQLException e) {
				e.printStackTrace();
			}
		
			pstmt = null;
			stmt = null;
			rs = null;
			try {
				String query1 = "select music.chartscore from music where music.register_num="+mnumber;
				String query2 = "update music set chartscore=? where music.register_num="+mnumber;
				String query3 = "select user_.coin from user_ where user_.user_num="+user_num;
				String query4 = "update user_ set coin=? where user_.user_num="+user_num;
				pstmt = conn.prepareStatement(query2);
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query1);
				int originScore=0;
				while (rs.next()) {
					originScore = rs.getInt(1);
					if (originScore==0) {
						music_cnt();
						System.out.println("\nOne music newly entered the Chart!");
					}
				}
				
				pstmt.setInt(1, originScore+1);
				int r = pstmt.executeUpdate();
				if (r>=1) {
					System.out.println("number "+mnumber+" music's score up");
				}
				else {
					System.out.println("Score up failed");
				}
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				pstmt = conn.prepareStatement(query4);
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query3);
				int originCoin = 0;
				while (rs.next()) {
					originCoin = rs.getInt(1);
				}
				
				pstmt.setInt(1, originCoin-1000);
				r = pstmt.executeUpdate();
				if (r>=1) {
					System.out.println(id+"'s coin decreased\n");
					coin = coin-1000;
				}
				else {
					System.out.println("Coin decreasing failed\n");
				}
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				after_userlog();
				return;
			 
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		case 7:
			//음악 delete
			stmt = null;
			rs = null;
			try {
				String query = "select music.title, music.artist, music.register_num from music, reg_in_pla where reg_in_pla.user_num="+user_num+" and music.register_num= reg_in_pla.register_num";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				
				int cnt=0;
				System.out.println("----------------------------------------------------------------");
				System.out.println("Title\t\t\t"+"Artist\t\t\t"+"Register number\t\t\t");
				System.out.println("----------------------------------------------------------------");
				
				while (rs.next()) {
					cnt++;
					System.out.printf("%-24s", rs.getString(1));
					System.out.printf("%-24s", rs.getString(2));
					System.out.printf("%-24s", rs.getString(3));
					System.out.println("\n");
				}
				System.out.println("----------------------------------------------------------------");
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				if (cnt==0) {
					System.out.println("There is No Music to Delete\n");
					after_managerlog();
					return;
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
			pstmt = null;
			stmt = null;
			rs = null;
			System.out.print("Select music to delete by Register number: ");
			mnumber = scan.nextInt();
			try {
				String query = "delete from reg_in_pla where reg_in_pla.register_num="+mnumber+" and reg_in_pla.user_num="+user_num;
				stmt = conn.createStatement();
				int t = stmt.executeUpdate(query);
				if (t>=1) {
					System.out.println("Successfully Deleted\n");
				}
				else {
					System.out.println("There is no such Music\n");
				}
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {}
				after_userlog();
				return;
				
			}catch (SQLException e) {
				e.printStackTrace();
			}
			
		case 8:
			//user 정보
			stmt = null;
			rs = null;
			try {
				String query = "select user_.name_, user_.sex,  user_.bdate, user_.address, user_.email,"
						+ "user_.id, user_.user_num, user_.manager_num from user_ where user_.user_num="+user_num;
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				
				if (rs.next()) {
					System.out.println("name: "+rs.getString(1));
					System.out.println("sex: "+rs.getString(2));
					System.out.println("birth date: "+rs.getString(3));
					System.out.println("address: "+rs.getString(4));
					System.out.println("email: "+rs.getString(5));
					System.out.println("id: "+rs.getString(6));
					System.out.println("user number: "+rs.getString(7));
					System.out.println("manager number: "+rs.getString(8));
				}
				else {
					System.out.println("View Error");
				}
				System.out.print("\n");
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				after_userlog();
				return;
			} catch (SQLException e) {
				e.printStackTrace();
			}

		case 9:
			//회원 탈퇴
			System.out.println("Enter your id and user number");
			System.out.print("ID: ");
			String usrid = scan.next();
			System.out.print("User number: ");
			int usrnum = scan.nextInt();
		
			stmt = null;

			try {
				String query = "delete from user_ where user_.id='"+usrid+"' and user_.user_num="+usrnum;
				stmt = conn.createStatement();
				int r = stmt.executeUpdate(query);
				
				System.out.println("Successfully Withdrawed\n");
				
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				userMenu();
				return;
				
			} catch (SQLException e) {
				e.printStackTrace();
			}
		default:
			System.out.println("Invalid input, Select again\n");
			after_userlog();
			break;
		}
 	}
 	
 	public static void managerMenu() {
 		System.out.println("------------------------");
 		System.out.println("0. Return to Main Menu");
 		System.out.println("1. Log in as Manager");
 		System.out.println("------------------------");
		System.out.print("Input: ");
		input = scan.nextInt();
		System.out.print('\n');
		switch(input) {
		case 0:
			startMenu();
			return;
		case 1:
			manager_log();
			return;
		default:
			System.out.println("Invalid input, Select again\n");
			managerMenu();
			return;
		}
 	}
 	
 	public static void manager_log() {
 		System.out.print("Manager_num: ");
		manager_num = scan.nextInt();
		System.out.print("RRN: ");
		rrn = scan.next();
		System.out.print('\n');
		//두개 다 해당하는 tuple이 존재하면, 아래부분 수행
		Statement stmt = null;
		ResultSet rs = null;

		try {
			String query = "select manager.name_, manager.rrn, manager.sex, manager.bdate, manager.manager_num from manager where manager.manager_num="+manager_num+" and manager.rrn='"+rrn+"'";
			
			stmt = conn.createStatement();
			rs = stmt.executeQuery(query);
			
			if(rs.next()) {
				name = rs.getString(1);
				rrn = rs.getString(2);
				sex = rs.getString(3);
				bdate = rs.getString(4);
				manager_num = rs.getInt(5);
				System.out.println("Log in as manager number "+manager_num+'\n');
				
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				after_managerlog();
				return;
			}
			else {
				System.out.println("There is No such Manager\n");
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				managerMenu();
				return;
			}
		}catch (SQLException e) {
			e.printStackTrace();
		}
 	}
 	
 	public static void after_managerlog() {
 		Statement stmt = null;
 		ResultSet rs = null;
 		PreparedStatement pstmt = null;
 		System.out.println("--------------------------------");
 		System.out.println("0. Log out");
 		System.out.println("1. View Music");
 		System.out.println("2. Add new music to MusicList");
		System.out.println("3. Delete music from MusicList");
		System.out.println("4. View Users");
		System.out.println("5. Manage Users");
		System.out.println("--------------------------------");
		System.out.print("Input: ");
		input = scan.nextInt();
		System.out.print('\n');
		switch(input) {
		case 0:
			managerMenu();
			return;
		case 1:
			stmt = null;
			rs = null;
			try {
				String query = "select music.title, music.artist from music";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				
				int cnt=0;
				System.out.println("----------------------------------");
				System.out.println("Title\t\t\t"+"Artist\t\t\t");
				System.out.println("----------------------------------");
				while (rs.next()) {
					cnt++;
					System.out.printf("%-24s", rs.getString(1));
					System.out.printf("%-24s", rs.getString(2));
					System.out.print("\n");
				}
				System.out.println("----------------------------------");
				System.out.print('\n');
				if (cnt==0) {
					if (rs!=null) try {rs.close();} catch(SQLException e) {};
					if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
					after_managerlog();
					return;
				}
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
			
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
			try {
				System.out.println("To see more Detailed information, enter the title. If not, enter '0'");
				System.out.print("Input: ");
				String mtitle = scan.nextLine();
				mtitle = scan.nextLine();
				if (mtitle.equals("0")) {
					System.out.print("\n");
					after_managerlog();
					return;
				}
				String query = "select music.genre, music.album, music.release_date, music.lyricist, music.composer, music.title, music.artist, music.chartscore, music.price, music.register_num "
						+ "from music where music.title='"+mtitle+"'";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
	
				if (rs.next()) {
					System.out.println("Genre: "+rs.getString(1));
					System.out.println("Album: "+rs.getString(2));
					System.out.println("Release_date: "+rs.getString(3));
					System.out.println("Lyricist: "+rs.getString(4));
					System.out.println("Composer: "+rs.getString(5));
					System.out.println("Title: "+rs.getString(6));
					System.out.println("Artist: "+rs.getString(7));
					System.out.println("ChartScore: "+rs.getInt(8));
					System.out.println("Price: "+rs.getInt(9));
					System.out.println("Register_num : "+rs.getInt(10)+"\n");
					
				}
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				after_managerlog();
				return;
			} catch (SQLException e) {
				e.printStackTrace();
			}
		case 2:
			//음악 추가
			pstmt = null;
			stmt = null;
			rs = null;
			System.out.println("Genre");
	 		System.out.println("1. ballade\n2. dance\n3. classic\n4. agitation\n5. etc");
	 		System.out.print("Input: ");
			input = scan.nextInt();
			System.out.print('\n');
			if (input!=1 && input!=2 && input!=3 && input!=4 && input!=5) {
				System.out.println("Invalid input");
				after_managerlog();
				break;
			}
			
			if (input==manager_num) {
				genre = GENRE[input-1];
			}
			else {
				System.out.println("No permissions, you can only add music of "+GENRE[manager_num-1]);
				System.out.println("Return to previous menu\n");
				after_managerlog();
				return;
			}
			System.out.print("Album: ");
			scan.next();
			album = scan.nextLine();
			System.out.print("Release_date: ");
			release_date = scan.nextLine();
			System.out.print("Title: ");
			title = scan.nextLine();
			System.out.print("Artist: ");
			artist = scan.nextLine();
			System.out.print("Lyricist: ");
			lyricist = scan.nextLine();
			System.out.print("Composer: ");
			composer = scan.nextLine();
			price = 1000;
			register_num = ++REGISTER_NUM;
			manager_num = manager_num;
			chart_name = "TopChart";
			
			try {
				String query ="insert into music(genre, album, release_date, lyricist, composer, title, artist, chartscore, price, register_num, manager_num, chart_name) values(?,?,?,?,?,?,?,?,?,?,?,?)";
				
				pstmt=conn.prepareStatement(query);
				pstmt.setString(1, genre);
				pstmt.setString(2, album);
				pstmt.setString(3, release_date);
				pstmt.setString(4, lyricist);
				pstmt.setString(5, composer);
				pstmt.setString(6, title);
				pstmt.setString(7, artist);
				pstmt.setInt(8, chartscore);
				pstmt.setInt(9, price);
				pstmt.setInt(10, register_num);
				pstmt.setInt(11, manager_num);
				pstmt.setString(12, chart_name);
				
				int r = pstmt.executeUpdate();
				if (r<1) {
					REGISTER_NUM--;
					System.out.println("Adding Failed\n");
				}
				else {
					System.out.println("Successfully Added\n");
				}
				if (pstmt!=null) try {pstmt.close();} catch(SQLException e) {};
				
				after_managerlog();
				return;				
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		case 3:
			stmt = null;
			rs = null;
			try {
				String query = "select music.title, music.artist, music.genre, music.register_num from music";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				
				int cnt=0;
				System.out.println("----------------------------------------------------------------------------------------");
				System.out.println("Title\t\t\t"+"Artist\t\t\t"+"Genre\t\t\t"+"Register number");
				System.out.println("----------------------------------------------------------------------------------------");
		
				while (rs.next()) {
					cnt++;
					System.out.printf("%-24s", rs.getString(1));
					System.out.printf("%-24s", rs.getString(2));
					System.out.printf("%-24s", rs.getString(3));
					System.out.print(rs.getString(4));
					System.out.print('\n');
				}
				System.out.println("----------------------------------------------------------------------------------------");
				System.out.print('\n');
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				if (cnt==0) {
					System.out.println("There is No Music to Delete\n");
					after_managerlog();
					return;
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
			stmt = null;
			rs = null;
			
			System.out.print("Select music to delete by Register number\nInput: ");
			int mnumber = scan.nextInt();
			System.out.print('\n');
			
			try {
				String query = "select music.genre from music where music.register_num="+mnumber;
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				
				if (rs.next()) {
					String tmpgen = rs.getString(1);
					if (tmpgen.equals(GENRE[manager_num-1])==false) {
						System.out.println("No permissions, you can only delete music of "+GENRE[manager_num-1]+'\n');
						after_managerlog();
						return;
					}
				}
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
			pstmt = null;
			stmt = null;
			rs = null;
			
			try {
				String query = "delete from music where music.register_num="+mnumber;
				stmt = conn.createStatement();
				int t = stmt.executeUpdate(query);
				if (t>=1) {
					System.out.println("Successfully Deleted\n");
					
				}
				else {
					System.out.println("There is no such Music\n");
				}
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				after_managerlog();
				return;
				
			} catch (SQLException e) {
				e.printStackTrace();
			}
			
		case 4:
			stmt = null;
			rs = null;
			int cnt=0;
			//모든 user를 보여준다
			try {
				String query = "select user_.name_, user_.id, user_.user_num from user_";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				cnt=0;
				System.out.println("-------------------------------------------------------------");
				System.out.println("Name\t\t\t"+"Id\t\t\t"+"User Number");
				System.out.println("-------------------------------------------------------------");
				
				while (rs.next()) {
					cnt++;
					System.out.printf("%-24s", rs.getString(1));
					System.out.printf("%-24s", rs.getString(2));
					System.out.println(rs.getInt(3));
				}
				System.out.println("-------------------------------------------------------------");
				System.out.printf("\n");
				
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				if(cnt==0) {
					System.out.println("There is no User\n");
				}
				after_managerlog();
				return;
			}catch (SQLException e) {
				e.printStackTrace();
			}
		case 5:
			stmt = null;
			rs = null;
			cnt=0;
			try {
				String query = "select user_.name_, user_.id, user_.user_num from user_";
				
				stmt = conn.createStatement();
				rs = stmt.executeQuery(query);
				cnt=0;
				
				System.out.println("-------------------------------------------------------------");
				System.out.println("Name\t\t\t"+"Id\t\t\t"+"User Number");
				System.out.println("-------------------------------------------------------------");
				while (rs.next()) {
					cnt++;
					System.out.printf("%-24s", rs.getString(1));
					System.out.printf("%-24s", rs.getString(2));
					System.out.println(rs.getInt(3));
				}
				System.out.println("-------------------------------------------------------------");
				System.out.printf("\n");
				
				if (rs!=null) try {rs.close();} catch(SQLException e) {};
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				if(cnt==0) {
					System.out.println("There is no User\n");
					after_managerlog();
					return;
				}
			}catch (SQLException e) {
				e.printStackTrace();
			}
			
			pstmt = null;
			stmt = null;
			rs = null;
			
			try {
				System.out.print("Select user by user number to delete\nInput: ");
				int input = scan.nextInt();
				
				if (input%5==0) {
					input = 0;
				}
				
				if (input%5!=manager_num) {
					System.out.println("No permissions, you can only delete only users under your control\n");
					after_managerlog();
					return;	
				}
				
				String query = "delete from user_ where user_.user_num = "+input;
				stmt = conn.createStatement();
				int t = stmt.executeUpdate(query);
				if (t>=1) {
					System.out.println("Successfully Deleted\n");
				}
				else {
					System.out.println("There is no such Music\n");
				}
				if (stmt!=null) try {stmt.close();} catch(SQLException e) {};
				
				after_managerlog();
				return;
				
			} catch (SQLException e) {
				e.printStackTrace();
			}
		default:
			System.out.println("Invalid input, Select again\n");
			after_managerlog();
			break;
		}
 	}
 	
	public static void main(String[] args) throws SQLException
	{
		try {
			Class.forName("org.mariadb.jdbc.Driver");
			String url = "jdbc:mariadb://localhost:3306/MusicApp";
			String user = "db";
			String psw = "db!";
			conn = DriverManager.getConnection(url, user, psw);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		
		ini_USERNUM();
		ini_REGISTERNUM();
		startMenu();
		
		if(conn != null) try{ conn.close();} catch(SQLException e){e.printStackTrace();}
	}
}