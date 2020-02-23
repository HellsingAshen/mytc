package com.git.service;

import com.git.dao.IAccountDao;
import com.git.domain.Account;
import com.git.utils.TransactionManager;

import java.util.List;

public class AccountServiceImpl implements IAccountService {

	public IAccountDao getAccountDao() {
		return accountDao;
	}

	public void setAccountDao(IAccountDao accountDao) {
		this.accountDao = accountDao;
	}

	private IAccountDao accountDao;

	public void setTransactionManager(TransactionManager transactionManager) {
		this.transactionManager = transactionManager;
	}

	private TransactionManager transactionManager;

	public void saveAccount(Account account) {
		accountDao.saveAccount(account);
	}

	public void deleteAccount(Integer id) {
		try {
			transactionManager.beginTransaction();
			accountDao.deleteAccount(id);
			transactionManager.commit();
		} catch (Exception e){
			transactionManager.rollback();
		} finally {
			transactionManager.release();
		}
	}

	public void updateAccount(Account account) {
		try {
			transactionManager.beginTransaction();
			accountDao.updateAccount(account);
			transactionManager.commit();
		} catch (Exception e){
			transactionManager.rollback();
		} finally {
			transactionManager.release();
		}
	}

	public List<Account> findAllAccount() {
		try {
			transactionManager.beginTransaction();
			List<Account> accounts = accountDao.findAllAccount();
			transactionManager.commit();
			return accounts;
		} catch (Exception e){
			transactionManager.rollback();
			throw  new RuntimeException(e);
		} finally {
			transactionManager.release();
		}
	}

	public Account findAccountById(Integer id) {
		try {
			transactionManager.beginTransaction();
			Account account = accountDao.findAccountById(id);
			transactionManager.commit();
			return account;
		} catch (Exception e){
			transactionManager.rollback();
			throw  new RuntimeException(e);
		} finally {
			transactionManager.release();
		}
	}


	public void transferAccount(String outName, String inName, float money) {
		// 1. get outAccount
		// 2. get inAccount
		// 3. outAccount min money
		// 4. inAccount plus money
		// 6. update outAccount
		// 7. update inAccount
		try {
			transactionManager.beginTransaction();
			Account outAcc = accountDao.findAccountByName(outName);
			Account inAcc = accountDao.findAccountByName(inName);

			outAcc.setMoney(outAcc.getMoney() - money);
			inAcc.setMoney(inAcc.getMoney() + money);
			accountDao.updateAccount(outAcc);
			int i = 10 / 0;
			accountDao.updateAccount(inAcc);
			transactionManager.commit();
		} catch (Exception e){
			transactionManager.rollback();
			System.out.println("-------------In roll back\n");;
			e.printStackTrace();
			throw  new RuntimeException(e);
		} finally {
			transactionManager.release();
		}
	}
}
