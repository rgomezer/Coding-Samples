DECLARE
  v_emply_num      NUMBER;
  v_max          employee.salary%TYPE;
  v_min          employee.salary%TYPE;
  v_avg          employee.salary%TYPE;
  v_dept_id      department.department_id%TYPE;
  v_dept_name    department.department_name%TYPE;
  v_emply_num_dept  NUMBER;
  v_max_dept      employee.salary%TYPE;
  v_min_dept      employee.salary%TYPE;
  v_avg_dept      employee.salary%TYPE;
  
  CURSOR c_dept IS
        SELECT   	department_id, department_name
        FROM 	  	department
        ORDER BY 	department_name;
BEGIN
  SELECT COUNT(*)
    INTO v_emply_num
    FROM employee;
    
  DBMS_OUTPUT.PUT_LINE(RPAD('NUMBER OF EMPLOYEES', 50) || LPAD(TO_CHAR(v_emply_num),11));
  DBMS_OUTPUT.PUT_LINE(LPAD('-', 61, '-'));
  
  SELECT MAX(salary + NVL(commission, 0)), MIN(salary + NVL(commission, 0)), AVG(salary + NVL(commission, 0))
  INTO v_max, v_min, v_avg
  FROM employee;
  
  DBMS_OUTPUT.PUT_LINE(RPAD('COMPANY MAXIMUM SALARY:', 50) || TO_CHAR(v_max, '$99,990.00'));
  DBMS_OUTPUT.PUT_LINE(RPAD('COMPANY MINIMUM SALARY:', 50) || TO_CHAR(v_min, '$99,990.00'));
  DBMS_OUTPUT.PUT_LINE(RPAD('COMPANY AVERAGE SALARY:', 50) || TO_CHAR(v_avg, '$99,990.00'));  
  DBMS_OUTPUT.PUT_LINE(LPAD('-', 61, '-'));
  
  DBMS_OUTPUT.PUT_LINE(RPAD('COMPANY AVERAGE SALARY (54%):', 50) || TO_CHAR(0.54 * v_max, '$99,990.00'));  
  DBMS_OUTPUT.PUT_LINE(LPAD('-', 61, '-'));
   
  OPEN c_dept;
  FETCH	c_dept INTO v_dept_id, v_dept_name;
  
  IF c_dept%NOTFOUND THEN
    DBMS_OUTPUT.PUT_LINE('No entry in DEPARTMENT table!');
  ELSE
    LOOP       
      SELECT COUNT(*), MAX(salary + NVL(commission, 0)), MIN(salary + NVL(commission, 0)), AVG(salary + NVL(commission, 0))
          INTO v_emply_num_dept, v_max_dept, v_min_dept, v_avg_dept
          FROM employee
          WHERE department_id = v_dept_id;      
      IF v_emply_num_dept >= 1 AND v_avg_dept > 0.54 * v_max THEN
        DBMS_OUTPUT.PUT_LINE(RPAD('DEPARTMENT NAME:', 50) || LPAD(v_dept_name, 11));
        DBMS_OUTPUT.PUT_LINE(RPAD('NUMBER OF EMPLOYEES:', 50) || LPAD(TO_CHAR(v_emply_num_dept), 11));  
        DBMS_OUTPUT.PUT_LINE(RPAD('MAXIMUM SALARY:', 50) || TO_CHAR(v_max_dept, '$99,990.00'));
        DBMS_OUTPUT.PUT_LINE(RPAD('MINIMUM SALARY:', 50) || TO_CHAR(v_min_dept, '$99,990.00'));
        DBMS_OUTPUT.PUT_LINE(RPAD('AVERAGE SALARY:', 50) || TO_CHAR(v_avg_dept, '$99,990.00'));  
        DBMS_OUTPUT.PUT_LINE(LPAD('-', 61, '-')); 
      END IF;
      FETCH	c_dept INTO v_dept_id, v_dept_name;
      EXIT WHEN c_dept%NOTFOUND; 
    END LOOP;
  END IF;
  CLOSE c_dept;
END;