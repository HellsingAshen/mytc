package com.git.dao;

import com.git.domain.Account;

import java.util.List;

public interface IAccountDao {
	void saveAccount(Account account);
	
	void deleteAccount(Integer id);
	
	void updateAccount(Account account);

	List<Account> findAllAccount();

	Account findAccountByName(String name);

	Account findAccountById(Integer id);

	//void transferAccount(String outName, String inName, float money);

}
