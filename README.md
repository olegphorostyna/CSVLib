
CSV formatting and content restrictions (MODIFIED - https://www.ibm.com/support/knowledgecenter/SS3NGB_5.2.0/ioc/int_csvdata.html)

 - The first line of the CSV file must contain a list of the property names, which are separated by commas. 
 - Additional commas must be enclosed inside quotation marks. (1,"Other, time") 
 - Additional quotation mark must be guarded by another quotation mark (2, "Jnon ""Sun"" Philip")  
 - Each line after the first line of the CSV file must contain an identical number of values to match the property names in the            first line. 
 - There must be no extra commas at the end of any line and the number of commas on each line must be the same.
 - Every line in the CSV file must end up with newline character (/n).
 

CSVLib operates with raw data types (mainly strings) but it also can work with CSValizable instances.
CSValizable perform mapping of raw data (obtained from CSV) to user defined types (objects) and vice versa.
By overriding CSValizable.toCSV() or CSValizable.fromCSV() you can serialize (or deserialze) object
in CSV format file. 


Set data columns (define structure of the table - naming for each column):
	
	void createTable(string tab_name, vector columns_names)

Load table:
	
	void loadTable(istream file_stream)

Set column name:

	void setColName(int subscript, string name)

Set index (column that will be compared against search queries):

	void setIndex(int subscript);

Get values by column name:

	vector getCol(string name) 

Add row:

	void writeRow(vector coresponding_vals);
	void writeRow(CSValizable row); 

Get row by value compared with index (if whole==false) If whole is set to true whole table will be searched:

	vector readRow(string value_at_index,bool whole);
	CSValizable readRow(string value_at_index,bool whole);

Modify row:

	void modifyRow(vector coresponding_vals, string value_at_index, bool whole);
	void modifyRow(CSValizable row, string value_at_index, bool whole); 

Delete row:

	vector deleteRow(string value_at_index,bool whole);
	CSValizable deleteRow(string value_at_index,bool whole);

 



	

	




