
DECLARE 
  v_vin          auto_service.vin%TYPE;  
  v_service_num  NUMBER;
  v_first_date   auto_service.srv_date%TYPE;
  v_last_date    auto_service.srv_date%TYPE;
  v_min_price    auto_service.srv_price%TYPE;
  v_max_price    auto_service.srv_price%TYPE;
  v_first_price  auto_service.srv_price%TYPE;
  v_last_price   auto_service.srv_price%TYPE;
  v_min_date     auto_service.srv_date%TYPE;
  v_max_date     auto_service.srv_date%TYPE;
  
  CURSOR c_auto IS
        SELECT vin, MIN(srv_date)
        FROM auto_service
        GROUP BY vin
        HAVING MIN(srv_date) >= to_date('01-FEB-2008','DD-MON-YYYY')
        AND MIN(srv_date) < to_date('31-MAR-2013','DD-MON-YYYY')
        ORDER BY vin;
        
BEGIN
  OPEN c_auto;
  FETCH	c_auto INTO v_vin, v_first_date;
  IF c_auto%NOTFOUND THEN
    DBMS_OUTPUT.PUT_LINE('No VIN found in the time frame!');
  ELSE
    DBMS_OUTPUT.PUT_LINE(RPAD('VIN', 8) || RPAD('First Service Date (Price)', 30) 
       || RPAD('Last Service Date (Price)', 32) || RPAD('Min Price (Service Date)', 28) 
       || RPAD('Max Price (Service Date)', 28) || RPAD('# of Services', 16) );
    DBMS_OUTPUT.PUT_LINE(LPAD('=', 138, '='));
    LOOP
      SELECT COUNT(*), MIN(srv_date), MAX(srv_date), MIN(srv_price), MAX(srv_price)
        INTO v_service_num, v_first_date, v_last_date, v_min_price, v_max_price
        FROM auto_service
        WHERE vin = v_vin;
      
      SELECT srv_price
        INTO v_first_price
        FROM auto_service
        WHERE vin = v_vin AND srv_date = v_first_date;
      
      SELECT srv_price
        INTO v_last_price
        FROM auto_service
        WHERE vin = v_vin AND srv_date = v_last_date;
      
      SELECT srv_date
        INTO v_min_date
        FROM auto_service
        WHERE vin = v_vin AND srv_price = v_min_price;
     
      SELECT srv_date
        INTO v_max_date
        FROM auto_service
        WHERE vin = v_vin AND srv_price = v_max_price;

      DBMS_OUTPUT.PUT_LINE(RPAD(v_vin, 8) || LPAD(TO_CHAR(v_first_date) || ' (' || TO_CHAR(v_first_price, '$99,990.00') || ')' , 28)
       || LPAD(TO_CHAR(v_last_date) || ' (' || TO_CHAR(v_last_price, '$99,990.00') || ')', 28) 
       || LPAD(TO_CHAR(v_min_price, '$99,990.00') || ' (' || TO_CHAR(v_min_date) || ')', 28) 
       || LPAD(TO_CHAR(v_max_price, '$99,990.00') || ' (' || TO_CHAR(v_max_date) || ')', 28) || LPAD(v_service_num, 16));
       
      FETCH	c_auto INTO v_vin, v_first_date;
      EXIT WHEN c_auto%NOTFOUND; 
    END LOOP;
  END IF;
  CLOSE c_auto;
END;