package com.git.dao;

import com.git.domain.Account;
import com.git.utils.ConnectionUtils;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;

import java.sql.SQLException;
import java.util.List;

public class AccountDaoImpl implements IAccountDao {

	public QueryRunner getRunner() {
		return runner;
	}

	private QueryRunner runner;

	public void setConnectionUtils(ConnectionUtils connectionUtils) {
		this.connectionUtils = connectionUtils;
	}

	private ConnectionUtils connectionUtils;

	/**
	 * @param runner the runner to set
	 */
	public void setRunner(QueryRunner runner) {
		this.runner = runner;
	}

	public void saveAccount(Account account) {
		try {
			System.out.println("==== saveAccount " + connectionUtils.getThreadConnection() + "\n");

			runner.update(connectionUtils.getThreadConnection(),"insert into account (name, money) value (?, ?)", account.getName(), account.getMoney());
		} catch (SQLException e) {
			throw new RuntimeException(e);
			
		}
	}

	public void deleteAccount(Integer id) {
		try {
			runner.update(connectionUtils.getThreadConnection(),"delete from account where id = ?", id);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}


	public void updateAccount(Account account) {
		try {
			System.out.println("==== updateAccount " + connectionUtils.getThreadConnection() + "\n");
			System.out.println("==== updateAccount flag "
					+ connectionUtils.getThreadConnection().getAutoCommit() + "\n");

			runner.update(connectionUtils.getThreadConnection(),"update account set name = ?, money = ? where id = ?", account.getName(), account.getMoney(),
					account.getId());
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	public List<Account> findAllAccount() {
		try {
			return runner.query(connectionUtils.getThreadConnection(), "select * from account", new BeanListHandler<Account>(Account.class));
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	public Account findAccountById(Integer id) {
		try {
			return (Account) runner.query(connectionUtils.getThreadConnection(), "select * from account Where id = ?", new BeanHandler<Account>(Account.class),
					id);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	public Account findAccountByName(String name) {
		try {
			List<Account> accounts =  runner.query(connectionUtils.getThreadConnection(), "select * from account Where name = ?",
					new BeanListHandler<Account>(Account.class), name);
			if (accounts == null || accounts.size() == 0) {
				return null;
			} else if (accounts.size() > 1) {
				throw new RuntimeException("data in db is invalid.");
			} else {
				return accounts.get(0);
			}
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}
//	@Override
//	public void transferAccount(String outName, String inName, float money) {
//		// 1. get outAccount
//		// 2. get inAccount
//		// 3. outAccount min money
//		// 4. inAccount plus money
//		// 6. update outAccount
//		// 7. update inAccount
//		Account outAcc = findAccountByName(outName);
//		Account inAcc = findAccountByName(inName);
//
//		outAcc.setMoney(outAcc.getMoney() - money);
//		inAcc.setMoney(inAcc.getMoney() + money);
//		updateAccount(outAcc);
//		updateAccount(inAcc);
//	}

}
