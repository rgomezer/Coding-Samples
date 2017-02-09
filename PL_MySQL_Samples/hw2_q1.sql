ACCEPT p_1 PROMPT 'Please enter an employee ID:'

DECLARE
  c_pad_length1   CONSTANT NUMBER := 15;
  c_pad_length2   CONSTANT NUMBER := 21;
  v_input_emp_id	NUMBER := &p_1;
  v_emp_name      employee.employee_name%TYPE;
  v_hire_date     employee.hire_date%TYPE;
  v_total_pay     employee.salary%TYPE;
  v_mngr_id       employee.manager_id%TYPE;
  v_mngr_name     employee.employee_name%TYPE;
  v_hire_date2    employee.hire_date%TYPE;
  v_total_pay2    employee.salary%TYPE;
  v_dpm_id        department.department_id%TYPE;
  v_dpm_name      department.department_name%TYPE;
  v_emp_count     NUMBER;
  v_pay_sum       employee.salary%TYPE;
  v_pay_sum2      employee.salary%TYPE;
  v_n				      NUMBER;

BEGIN
  DBMS_OUTPUT.PUT_LINE('User Input:');
  DBMS_OUTPUT.PUT_LINE(TO_CHAR(v_input_emp_id));
  DBMS_OUTPUT.PUT_LINE('My Output:'); 
  
  SELECT 	COUNT(*)
    INTO		v_n
    FROM		employee
    WHERE		employee_id = v_input_emp_id;

  IF v_n != 1 THEN
    DBMS_OUTPUT.PUT_LINE(TO_CHAR(v_input_emp_id) || ' is not in the EMPLOYEE table.');
  ELSE
    SELECT employee_name, manager_id, hire_date, salary + NVL(commission, 0), department_id
    INTO   v_emp_name, v_mngr_id, v_hire_date, v_total_pay, v_dpm_id
    FROM   employee
    WHERE  employee_id = v_input_emp_id;
    
    DBMS_OUTPUT.PUT_LINE('------- Employee -------');
 		DBMS_OUTPUT.PUT_LINE(RPAD('Name:', c_pad_length1) || v_emp_name);
    DBMS_OUTPUT.PUT_LINE(RPAD('Hire Date:', c_pad_length1) || TO_CHAR(v_hire_date, 'DD-MON-YYYY'));
    DBMS_OUTPUT.PUT_LINE(RPAD('Total Pay:', c_pad_length1) || TRIM(TO_CHAR(v_total_pay, '$99,990.00')));
    DBMS_OUTPUT.PUT_LINE('------- Manager -------');
    
    IF v_mngr_id IS NOT NULL THEN
      SELECT employee_name, hire_date, salary + NVL(commission, 0)
      INTO   v_mngr_name, v_hire_date2, v_total_pay2
      FROM   employee
      WHERE  employee_id = v_mngr_id;      
      DBMS_OUTPUT.PUT_LINE(RPAD('Name:', c_pad_length1) || v_mngr_name);
      DBMS_OUTPUT.PUT_LINE(RPAD('Hire Date:', c_pad_length1) || TO_CHAR(v_hire_date2, 'DD-MON-YYYY'));
      DBMS_OUTPUT.PUT_LINE(RPAD('Total Pay:', c_pad_length1) || TRIM(TO_CHAR(v_total_pay2, '$99,990.00')));
    ELSE
      DBMS_OUTPUT.PUT_LINE(RPAD('Name:', c_pad_length1) || 'N/A');
      DBMS_OUTPUT.PUT_LINE(RPAD('Hire Date:', c_pad_length1) || 'N/A');
      DBMS_OUTPUT.PUT_LINE(RPAD('Total Pay:', c_pad_length1) || 'N/A');
    END IF;
    
    DBMS_OUTPUT.PUT_LINE('------- Department -------');
    IF v_dpm_id IS NOT NULL THEN
      SELECT department_name
      INTO   v_dpm_name
      FROM   department
      WHERE  department_id = v_dpm_id;
      
      SELECT COUNT(*)
      INTO   v_emp_count
      FROM   employee
      WHERE  department_id = v_dpm_id;
      
      DBMS_OUTPUT.PUT_LINE(RPAD('Name:', c_pad_length2) || v_dpm_name);
      DBMS_OUTPUT.PUT_LINE(RPAD('Number of Employees:', c_pad_length2) || TO_CHAR(v_emp_count));
    ELSE
      DBMS_OUTPUT.PUT_LINE(RPAD('Name:', c_pad_length2) || 'N/A');
      DBMS_OUTPUT.PUT_LINE(RPAD('Number of Employees:', c_pad_length2) || '0');
    END IF;
    
    DBMS_OUTPUT.PUT_LINE('------- Company -------');
    SELECT COUNT(*), SUM(salary + NVL(commission, 0))
    INTO   v_emp_count, v_pay_sum2
    FROM   employee;
    DBMS_OUTPUT.PUT_LINE(RPAD('Sum of Total Pay:', c_pad_length2) || TRIM(TO_CHAR(v_pay_sum2, '$99,990.00')));
  END IF;
END;